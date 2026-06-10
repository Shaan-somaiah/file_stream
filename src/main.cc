#include <gflags/gflags.h>
#include <glog/logging.h>
#include <iostream>
#include <file_stream/file_stream.h>

int main(int argc, char* argv[]) {
    FLAGS_log_dir = "/var/log/file_stream_logs";

    google::InitGoogleLogging(argv[0]);
    google::ParseCommandLineFlags(&argc, &argv, true);

    std::cerr << "Logging to directory " << FLAGS_log_dir << '\n';

    google::ShutdownGoogleLogging();
}
