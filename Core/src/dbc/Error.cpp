#include "Error.h"

namespace pap
{
namespace db
{


const char *toString(ErrorCode code)
{
    switch (code)
    {
    case ErrorCode::None:
        return "None";
    case ErrorCode::ColumnIndexOutOfRange:
        return "ColumnIndexOutOfRange";
    case ErrorCode::RowIndexOutOfRange:
        return "RowIndexOutOfRange";
    case ErrorCode::ColumnNameNotFound:
        return "ColumnNameNotFound";
    case ErrorCode::UnsupportedDriver:
        return "UnsupportedDriver";
    case ErrorCode::NoConnection:
        return "NoConnection";
    case ErrorCode::ConnectionFailed:
        return "ConnectionFailed";
    case ErrorCode::QueryFailed:
        return "QueryFailed";
    case ErrorCode::TransactionFailed:
        return "TransactionFailed";
    case ErrorCode::SchemaSwitchFailed:
        return "SchemaSwitchFailed";
    default:
        return "Unknown";
    }
}

Error::Error(ErrorCode c, const char *msg, const char *ctx) : code(c), message(msg ? msg : ""), context(ctx ? ctx : "")
{
}

std::string Error::toString() const
{
    std::string s;
    s.reserve(64);
    s += "[Error:";
    s += pap::db::toString(code);
    s += "]";
    if (message && *message)
    {
        s += " ";
        s += message;
    }
    if (context && *context)
    {
        s += " (ctx: ";
        s += context;
        s += ")";
    }
    return s;
}

std::ostream &operator<<(std::ostream &os, const Error &e)
{
    return os << e.toString();
}
} // namespace db
} // namespace pap
