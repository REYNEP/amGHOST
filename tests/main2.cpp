#include "amGHOST/amGHOST_System.hh"

int main(int argumentCount, char* argumentVector[]) 
{
    amGHOST_System::create_system();    // initializes amG_HEART
    
    amGHOST_Window* W = amG_HEART->new_window_interface();
    W->create(L"Whatever", 0, 0, 500, 600);

    REY::cin.get();     // wait for terminal input
    W->destroy();
}