#include <pineapple.h>


std::unique_ptr<pap::Application> pap::CreateApplication(){
    return std::make_unique<Application>();
}
