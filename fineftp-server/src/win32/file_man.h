/// @file

#ifndef FINEFTP_SERVER_SRC_WIN32_FILE_MAN_H_
#define FINEFTP_SERVER_SRC_WIN32_FILE_MAN_H_

#include <windows.h>

#include <cstdint>
#include <memory>
#include <string>

namespace fineftp
{

/// A memory mapped read-only file.
///
/// @note The implementation is NOT thread safe!
class ReadableFile
{
public:
  ReadableFile(const ReadableFile&)            = delete;
  ReadableFile& operator=(const ReadableFile&) = delete;
  ReadableFile(ReadableFile&&)                 = delete;
  ReadableFile& operator=(ReadableFile&&)      = delete;
  ~ReadableFile();

#if !defined(__GNUG__)
  using Str = std::wstring;
#else
  using Str = std::string;
#endif

  /// Retrieves the file at the specified path.
  ///
  /// @param pth      The path of the file.
  ///
  /// @param The requested file or nullptr if the file could not be retrieved.
  static std::shared_ptr<ReadableFile> get(const Str& pth);

  /// Returns the size of the file.
  ///
  /// @return The size of the file.
  std::size_t size() const;

  /// Returns a pointer to the beginning of the file contents.
  ///
  /// @return A pointer to the beginning of the file contents.
  const std::uint8_t* data() const;

  /// Returns the path of the file.
  ///
  /// @return The path of the file.
  const Str& path() const;

private:
  ReadableFile() = default;

  Str           pth_        = {};
  std::size_t   size_       = {};
  std::uint8_t* data_       = {};
  HANDLE        handle_     = INVALID_HANDLE_VALUE;
  HANDLE        map_handle_ = INVALID_HANDLE_VALUE;
};

inline std::size_t ReadableFile::size() const
{
  return size_;
}

inline const std::uint8_t* ReadableFile::data() const
{
  return data_;
}

inline const ReadableFile::Str& ReadableFile::path() const
{
  return pth_;
}

}

#endif  // FINEFTP_SERVER_SRC_WIN32_FILE_MAN_H_

