#include "DBWindow.h"


DBWindow::DBWindow(const std::string &title) : m_Title(title)
{
    // Connect to DB
    //authentication will be handled in gui later
    std::string user;
    std::cout << "user: ";
    std::getline(std::cin, user);

    std::string password;
    std::cout << "password: ";
    std::getline(std::cin, password);

    auto ok = pap::DBManager::connect(pap::DBDriver::MariaDB, "tcp://127.0.0.1:3306", user, password, "students");

    //todo: make gui
    if (!ok)
    {
        PAP_INFO("failed");
        return;
    }
    std::cout << "[DEBUG] Running query: SELECT * FROM student_info;" << std::endl;
    auto test = pap::DBManager::executeQuery("SELECT * FROM student_info;");
    if (!test)
    {
        std::cout << "aFailed query: " << test.error() << "\n";
        return;
    }
    m_Result = *test;
}

void DBWindow::drawImGui() {
    ImGui::Begin(m_Title.c_str());
    if (!drawTable())
        ImGui::TextUnformatted("No data loaded yet.");
    ImGui::End();
}

bool DBWindow::drawTable(){

        if (m_Result.getRowCount() == 0) {
            ImGui::TextUnformatted("No results to display.");
            return false;
        }

        const auto cols = m_Result.getColumnCount();
        const auto& colNames = m_Result.getColumnNames();

        if (ImGui::BeginTable("DBResultTable", static_cast<int>(cols), ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            // Header
            ImGui::TableHeadersRow();
            for (const auto& name : colNames) {
                ImGui::TableSetColumnIndex(static_cast<int>(&name - &colNames[0]));
                ImGui::TextUnformatted(name.c_str());
            }

            // Rows
            for (size_t r = 0; r < m_Result.getRowCount(); ++r) {
                ImGui::TableNextRow();
                auto rowRes = m_Result.getRow(r);
                auto row = pap::unwrap_or_else(rowRes, [&](const std::string& err) {
                    std::cerr << "Failed to get row: " << err << "\n";
                    return;
                });

                for (size_t c = 0; c < row.size(); ++c) {
                    ImGui::TableSetColumnIndex(static_cast<int>(c));
                    ImGui::TextUnformatted(row[c].c_str());
                }
            }

            ImGui::EndTable();
        }
        return true;

    }
