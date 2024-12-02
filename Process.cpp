#include "framework.h"
#include "Process.h"


Process* Process::Instance()
{
    //if (instance == nullptr)
    //{
    //    instance = ;
    //}
    return new Process;
}

Process::Process()
{

}

void Process::Update()
{
}

Process::~Process()
{
}
