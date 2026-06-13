#include <glog/logging.h>
#include <gflags/gflags.h>
#include <filesystem>
#include "file_stream/file_stream.h"

DEFINE_string(source_file, "" ,"Full path of file to be streamed");
DEFINE_string(destination_file, "" ,"Full path to the destination");
DEFINE_bool(overwrite, false, "Overwrite existing destination file");

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

    LOG(INFO) << "Creating destination file : " << m_destination_file; 
    if(!createFile(m_destination_file)) {
        LOG(FATAL) << "Unable to create destination file : " << m_destination_file;   
    }

    return (fileStream(m_source_file, m_destination_file));
}

bool myfs::FileEngine::validateFileExists(const fs::path& file) {
    if(fs::exists(file)) {
        LOG(INFO) << "File found : " << file;
        return true;
    }
    LOG(WARNING) << "File not found : " << file;
    return false;
}

bool myfs::FileEngine::fileStream(const std::filesystem::path& source_file, const std::filesystem::path& destination_file) {
    return true;
}
            
bool myfs::FileEngine::overwriteFileStream(const std::filesystem::path& source_file, const std::filesystem::path& destination_file) {
    return true;
}

bool myfs::FileEngine::createFile(const std::filesystem::path& file) {
    return true;
}