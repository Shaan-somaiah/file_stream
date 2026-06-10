#include <glog/logging.h>
#include <gflags/gflags.h>
#include <filesystem>
#include "file_stream/file_stream.h"

DEFINE_string(source_file, "" ,"Full path of file to be streamed");
DEFINE_string(destination_file, "" ,"Full path to the destination");
DEFINE_bool(overwrite, false, "Overwrite existing destination file");

namespace myfs = file_stream;
namespace fs = std::filesystem;

