#include "ChronoVault.h"
#include "httplib.h"
#include "json.hpp"
#include <iostream>
#include <mutex>
#include <filesystem>
using json = nlohmann::json;
int main(int argc, char** argv) {
    std::string publicDir = argc > 1 ? argv[1] : "public";
    ChronoVault vault; httplib::Server server; std::mutex mutex;
    auto missionJson = [](const Mission& m) { return json{{"id",m.id()},{"name",m.name()},{"timeline",m.timeline()},{"explorerType",m.explorerType()},{"energy",m.energy()},{"status",m.status()},{"result",m.result()}}; };
    server.Get("/api/dashboard", [&](const httplib::Request&, httplib::Response& res) {
        std::lock_guard<std::mutex> lock(mutex); int completed=0; for(const auto& m:vault.missions()) if(m.status()=="Completed") ++completed;
        json recent=json::array(); for(auto it=vault.missions().rbegin();it!=vault.missions().rend() && recent.size()<4;++it) recent.push_back(missionJson(*it));
        res.set_content(json{{"missions",vault.missions().size()},{"energy",vault.energy()},{"explorers",vault.explorers().size()},{"completed",completed},{"recent",recent}}.dump(),"application/json");
    });
    server.Get("/api/missions", [&](const httplib::Request&, httplib::Response& res) { std::lock_guard<std::mutex> lock(mutex); json a=json::array(); for(const auto& m:vault.missions()) a.push_back(missionJson(m)); res.set_content(a.dump(),"application/json"); });
    server.Get("/api/explorers", [&](const httplib::Request&, httplib::Response& res) { json a=json::array(); for(const auto& e:vault.explorers()) a.push_back({{"name",e->name()},{"type",e->type()},{"action",e->action()}}); res.set_content(a.dump(),"application/json"); });
    server.Post("/api/missions", [&](const httplib::Request& req, httplib::Response& res) { try { auto b=json::parse(req.body); std::lock_guard<std::mutex> lock(mutex); auto& m=vault.createMission(b.value("name",std::string{}),b.value("timeline",std::string{}),b.value("explorerType",std::string{}),b.value("energy",0)); res.status=201; res.set_content(missionJson(m).dump(),"application/json"); } catch(const std::exception& e) { res.status=400; res.set_content(json{{"error",e.what()}}.dump(),"application/json"); } });
    server.Post(R"(/api/missions/(\d+)/launch)", [&](const httplib::Request& req, httplib::Response& res) { try { int id=std::stoi(req.matches[1]); std::lock_guard<std::mutex> lock(mutex); vault.launchMission(id); for(const auto& m:vault.missions()) if(m.id()==id) { res.set_content(missionJson(m).dump(),"application/json"); return; } } catch(const std::exception& e) { res.status=400; res.set_content(json{{"error",e.what()}}.dump(),"application/json"); } });
    server.set_mount_point("/", publicDir);
    std::cout << "ChronoVault website: http://localhost:8099\nPress Ctrl+C to stop.\n";
    if (!server.listen("127.0.0.1",8099)) { std::cerr << "Could not start on port 8080. Close another app using it and retry.\n"; return 1; }
}
