#ifndef FILE_STREAM_H
#define FILE_STREAM_H

#include <gflags/gflags.h>
#include <filesystem>

DECLARE_string(source_file);
DECLARE_string(destination_file);
DECLARE_bool(overwrite);

namespace file_stream {
    class FileEngine {
        public:

            FileEngine() = delete;

            FileEngine(const std::filesystem::path& source_file, const std::filesystem::path& destination_file);

            void initialize();

            bool validateFileExists(const std::filesystem::path& file);

            bool fileStream(const std::filesystem::path& source_file, const std::filesystem::path& destination_file);
            
            bool overwriteFileStream(const std::filesystem::path& source_file, const std::filesystem::path& destination_file);

            bool createFile(const std::filesystem::path& file);

        private:
            const std::filesystem::path m_source_file;
            const std::filesystem::path m_destination_file;
    };

} // namespace file_stream

#endif // FILE_STREAM_H
