#pragma once

#include <windows.h>
#include <optional>
#include <string>
#include <vector>

namespace Usuario
{
    namespace Env
    {
        /**
         * @brief Obtiene el valor de una variable de entorno de Windows.
         *
         * Si la variable no existe, devuelve el valor por defecto proporcionado.
         *
         * @param Clave Nombre de la variable de entorno a obtener.
         * @param ValorDefault Valor que se devuelve si la variable no existe.
         * @return std::wstring Valor de la variable de entorno o ValorDefault si no existe.
         */
        std::wstring Obtener(const std::wstring &Clave, const std::wstring &ValorDefault)
        {
            // Tamaño de la variable de entorno
            DWORD Tamaño = GetEnvironmentVariableW(Clave.c_str(), nullptr, 0);
            if (Tamaño == 0 && GetLastError() == ERROR_ENVVAR_NOT_FOUND)
                return ValorDefault;

            // Obtener la variable de entorno
            std::vector<wchar_t> buffer(Tamaño);
            if (GetEnvironmentVariableW(Clave.c_str(), buffer.data(), Tamaño) == 0)
                return ValorDefault;

            // Retornar la variable obtenida
            return std::wstring(buffer.data());
        }
    }
}
