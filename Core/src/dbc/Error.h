#pragma once

#include <expected>
#include <format>
#include <ostream>
#include <string>

namespace pap
{
namespace db
{


enum class ErrorCode
{
    None = 0,
    ColumnIndexOutOfRange,
    RowIndexOutOfRange,
    ColumnNameNotFound,
    UnsupportedDriver,
    NoConnection,
    ConnectionFailed,
    QueryFailed,
    TransactionFailed,
    SchemaSwitchFailed,
    InvalidArgument,
    Unknown
};

const char *toString(ErrorCode code);

struct Error
{
    ErrorCode code{ErrorCode::Unknown};
    const char *message{""};
    const char *context{""};

    Error() = default;
    Error(ErrorCode c, const char *msg = "", const char *ctx = "");

    std::string toString() const;

    friend std::ostream &operator<<(std::ostream &os, const Error &e);
};


template <typename T>
using Result = std::expected<T, Error>;
} // namespace db
} // namespace pap

// C++20/23 std::formatter specialization
template <>
struct std::formatter<pap::db::Error> : std::formatter<std::string>
{
    auto format(const pap::db::Error &err, auto &ctx)
    {
        return std::formatter<std::string>::format(err.toString(), ctx);
    }
};
