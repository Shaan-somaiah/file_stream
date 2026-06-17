#include <gflags/gflags.h>
#include <glog/logging.h>
#include <iostream>
#include <file_stream/file_stream.h>

DECLARE_string(source_file);
DECLARE_string(destination_file);

int main(int argc, char* argv[]) {
    FLAGS_log_dir = "/var/log/file_stream_logs";

    google::InitGoogleLogging(argv[0]);
    google::ParseCommandLineFlags(&argc, &argv, true);

    std::cerr << "Logging to directory " << FLAGS_log_dir << '\n';

    CHECK_NE(FLAGS_source_file, "") << "--source_file required!!";
    CHECK_NE(FLAGS_destination_file, "") << "--destination_file required!!";

    file_stream::FileEngine i_FileEngine(FLAGS_source_file, FLAGS_destination_file);

    bool success = i_FileEngine.initialize();

    if(!success) {
        LOG(INFO) << "File stream failed";
    }

    google::ShutdownGoogleLogging();
}
