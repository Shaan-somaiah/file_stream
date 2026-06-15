#include <glog/logging.h>
#include <gflags/gflags.h>
#include <filesystem>
#include <fstream>
#include "file_stream/file_stream.h"

DEFINE_string(source_file, "" ,"Full path of file to be streamed");
DEFINE_string(destination_file, "" ,"Full path to the destination");
DEFINE_bool(overwrite, false, "Overwrite existing destination file");
DEFINE_string(default_directory, "/tmp/file_stream_dir" ,"Default directory to create destination file");

namespace myfs = file_stream;
namespace fs = std::filesystem;

myfs::FileEngine::FileEngine(const fs::path& source_file, const fs::path& destination_file)
    : m_source_file(source_file), m_destination_file(destination_file)
{

}

bool myfs::FileEngine::initialize() {

    LOG(INFO) << "Validating if source file " << m_source_file << " exists";
    if(!validateFileExists(m_source_file)) {
        LOG(FATAL) << "Provide valid source file!";
    }

    LOG(INFO) << "Validating if destination file " << m_destination_file << " exists";
    if(validateFileExists(m_destination_file)) {
        if(!FLAGS_overwrite) {
            LOG(FATAL) << "Destination file already exists, overwite with --overwrite";
        }
        LOG(WARNING) << "Overwring destination file " << m_destination_file;
        return (overwriteFileStream(m_source_file, m_destination_file));
    }

    LOG(INFO) << "Trying to create destination file : " << m_destination_file; 
    if(!createFile(m_destination_file)) {
        LOG(FATAL) << "Unable to create destination file : " << m_destination_file;   
    }

    return (fileStream(m_source_file, m_destination_file));
}

bool myfs::FileEngine::validateFileExists(const fs::path& file) {
   
    if(fs::exists(file) && !fs::is_directory(file)) {
        LOG(INFO) << "File found : " << file;
        return true;
    }
    LOG(WARNING) << "File not found : " << file;
    return false;
}

bool myfs::FileEngine::createFile(const std::filesystem::path& file) {

    LOG(INFO) << "Checking if " << file << " has a valid parent directory";
    if(!file.has_parent_path()) {
        LOG(WARNING) << "No parent directory supplied for " << file << " , creating the file under default directory : " << FLAGS_default_directory;

        VLOG(2) << "Checking if default directory " << FLAGS_default_directory<< " exists";
        if(fs::exists(FLAGS_default_directory) && fs::is_directory(FLAGS_default_directory)) {

            VLOG(2) << "Default directory " << FLAGS_default_directory << " exists";
            // create file in default directory and return status
            const fs::path full_path = FLAGS_default_directory / file;
            return (std::ofstream(full_path).good()); 

        }

        VLOG(2) << "Default directory " << FLAGS_default_directory << " does not exist, creating it";
        if(!fs::create_directories(FLAGS_default_directory)) {
            LOG(FATAL) << "Failed to create default directory " << FLAGS_default_directory;
        }
        VLOG(2) << "Default directory " << FLAGS_default_directory << " created";
        const fs::path full_path = FLAGS_default_directory / file;

        if(std::ofstream(full_path).good()) {
            LOG(INFO) << "File created under default directory : " << full_path;
            return true;
        }
        
        return false;
    }

    if(fs::exists(file.parent_path()) && fs::is_directory(file.parent_path())) { 
        LOG(INFO) << "Valid parent directory exists : " << file.parent_path();
        if(std::ofstream(file).good()) {
            LOG(INFO) << "Destination file created : " << file;
            return true;
        }
    }

    return false;
}


bool myfs::FileEngine::fileStream(const std::filesystem::path& source_file, const std::filesystem::path& destination_file) {
    return true;
}
            
bool myfs::FileEngine::overwriteFileStream(const std::filesystem::path& source_file, const std::filesystem::path& destination_file) {
    return true;
}
