// /src/main.cpp
#include <windows.h>
#include <string>
#include "AyudaServicio.hpp"

// -----------------------------------------------------------------------------
// Variables
// -----------------------------------------------------------------------------
SERVICE_STATUS VarEstado = {0};
SERVICE_STATUS_HANDLE HandServicio = nullptr;
HANDLE EventoPararServicio = nullptr;
#define SERVICIO L"Burst"

// -----------------------------------------------------------------------------
// Prototipos de funciones
// -----------------------------------------------------------------------------
void WINAPI Servicio(DWORD argc, LPWSTR *argv);
void WINAPI Controlador(DWORD flag);

// -----------------------------------------------------------------------------
// Punto de entrada del servicio
// -----------------------------------------------------------------------------
int wmain(int argc, wchar_t *argv[])
{
    SERVICE_TABLE_ENTRYW TablaServicios[] = {
        {const_cast<LPWSTR>(SERVICIO), (LPSERVICE_MAIN_FUNCTIONW)Servicio},
        {nullptr, nullptr}};

    return StartServiceCtrlDispatcherW(TablaServicios) ? 0 : 1;
}

// -----------------------------------------------------------------------------
// Función principal del servicio
// -----------------------------------------------------------------------------
void WINAPI Servicio(DWORD argc, LPWSTR *argv)
{
    HandServicio = RegisterServiceCtrlHandlerW(SERVICIO, Controlador);
    if (HandServicio == nullptr)
        return;
    Helpers::IniciarServicio(&VarEstado, HandServicio);

    // -----------------------------------------------------------------------------
    // Logica principal
    // -----------------------------------------------------------------------------
    EventoPararServicio = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    if (EventoPararServicio == nullptr)
    {
        Helpers::DetenerServicio(&VarEstado, HandServicio);
        return;
    }

    // Bucle principal simulado
    while (WaitForSingleObject(EventoPararServicio, 0) != WAIT_OBJECT_0)
    {
        // 
        Sleep(2000);
    }

    // -----------------------------------------------------------------------------
    // Fin de logica principal
    // -----------------------------------------------------------------------------

    CloseHandle(EventoPararServicio);
    Helpers::DetenerServicio(&VarEstado, HandServicio);
}

// -----------------------------------------------------------------------------
// Manejador de control del servicio
// -----------------------------------------------------------------------------
void WINAPI Controlador(DWORD flag)
{
    switch (flag)
    {
    case SERVICE_CONTROL_STOP:
    case SERVICE_CONTROL_SHUTDOWN:
        SetEvent(EventoPararServicio);
        break;

    default:
        break;
    }
}
