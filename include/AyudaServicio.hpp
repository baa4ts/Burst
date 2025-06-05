#pragma once

#include <windows.h>

namespace Helpers
{
    /**
     * @brief Inicializa y establece el estado del servicio como en ejecución.
     *
     * @param estado Puntero a la estructura SERVICE_STATUS del servicio.
     * @param handle Manejador del servicio obtenido a través de RegisterServiceCtrlHandler.
     * @param waitHint Tiempo estimado (en milisegundos) que tomará la transición de estados. Por defecto, 3000 ms.
     * @param usarSleep Indica si se debe hacer Sleep por el tiempo waitHint. Por defecto, false.
     */
    void WINAPI IniciarServicio(SERVICE_STATUS *estado, SERVICE_STATUS_HANDLE handle, DWORD waitHint = 3000, bool usarSleep = false)
    {
        ZeroMemory(estado, sizeof(SERVICE_STATUS));

        // ——————————————————————————————————————————————>
        // Establecer servicio en pendiente de inicio
        // ——————————————————————————————————————————————>
        estado->dwServiceType = SERVICE_WIN32_OWN_PROCESS;
        estado->dwControlsAccepted = 0;
        estado->dwCurrentState = SERVICE_START_PENDING;
        estado->dwWin32ExitCode = NO_ERROR;
        estado->dwServiceSpecificExitCode = 0;
        estado->dwCheckPoint = 1;
        estado->dwWaitHint = waitHint;
        SetServiceStatus(handle, estado);

        if (usarSleep)
        {
            Sleep(waitHint);
        }

        // ——————————————————————————————————————————————>
        // Establecer servicio en ejecución
        // ——————————————————————————————————————————————>
        estado->dwCurrentState = SERVICE_RUNNING;
        estado->dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
        estado->dwCheckPoint = 0;
        estado->dwWaitHint = 0;
        SetServiceStatus(handle, estado);
    }

    /**
     * @brief Cambia el estado del servicio a detenido.
     *
     * @param estado Puntero a la estructura SERVICE_STATUS del servicio.
     * @param handle Manejador del servicio obtenido a través de RegisterServiceCtrlHandler.
     * @param waitHint Tiempo estimado (en milisegundos) que tomará la transición de parada. Por defecto, 3000 ms.
     * @param usarSleep Indica si se debe hacer Sleep por el tiempo waitHint. Por defecto, false.
     */
    void WINAPI DetenerServicio(SERVICE_STATUS *estado, SERVICE_STATUS_HANDLE handle, DWORD waitHint = 3000, bool usarSleep = false)
    {
        // ——————————————————————————————————————————————>
        // Establecer servicio en pendiente de detención
        // ——————————————————————————————————————————————>
        estado->dwCurrentState = SERVICE_STOP_PENDING;
        estado->dwWin32ExitCode = NO_ERROR;
        estado->dwCheckPoint = 1;
        estado->dwWaitHint = waitHint;
        SetServiceStatus(handle, estado);

        if (usarSleep)
        {
            Sleep(waitHint);
        }

        // ——————————————————————————————————————————————>
        // Establecer servicio como detenido
        // ——————————————————————————————————————————————>
        estado->dwCurrentState = SERVICE_STOPPED;
        estado->dwCheckPoint = 0;
        estado->dwWaitHint = 0;
        SetServiceStatus(handle, estado);
    }
}