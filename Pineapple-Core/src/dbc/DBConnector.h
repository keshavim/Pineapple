#ifndef IDATABASE_H
#define IDATABASE_H

#include <core/core.h>
#include "DBResult.h"


namespace pap {

class DBConnector {
public:
    virtual ~DBConnector() = default;

    virtual Result<void> connect(const std::string& uri,
                         const std::string& user,
                         const std::string& password,
                         const std::string& database) = 0;

    virtual bool isConnected() const = 0;

    virtual Result<DBResult> executeQuery(const std::string& query) = 0;
};

} // namespace pap

#endif // IDATABASE_H
