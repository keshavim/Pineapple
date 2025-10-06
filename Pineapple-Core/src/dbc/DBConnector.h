#ifndef IDATABASE_H
#define IDATABASE_H

#include <string>
#include "DBResult.h"

namespace pap {

class DBConnector {
public:
    virtual ~DBConnector() = default;

    virtual bool connect(const std::string& uri,
                         const std::string& user,
                         const std::string& password,
                         const std::string& database) = 0;

    virtual bool isConnected() const = 0;

    virtual DBResult executeQuery(const std::string& query) = 0;
};

} // namespace pap

#endif // IDATABASE_H
