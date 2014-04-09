/*
  * (c) Copyright 2014 Franco Eusébio Garcia
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser GPL v3
  * as published by the Free Software Foundation.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
  * http://www.gnu.org/licenses/lgpl-3.0.txt for more details.
  *
  * You should have received a copy of the GNU Lesser GPL v3
  * along with this program; if not, write to the Free Software
  */

#include "GameEngineStd.h"

#include "SystemInformation.h"

namespace uge
{

    SystemInformation::SystemInformation() : m_pSigar(nullptr),
        m_CPUSpeed(0), m_TotalCPUCores(0), m_CPUCache(0), m_SystemRAM(0),
        m_FreeSystemRAM(0)
    {

    }

    SystemInformation::~SystemInformation()
    {
        Destroy();
    }

    bool SystemInformation::Init()
    {
        if (m_pSigar == nullptr)
        {
            sigar_open(&m_pSigar);
        }

        sigar_mem_t memory;
        if (sigar_mem_get(m_pSigar, &memory) != SIGAR_OK)
        {
            return false;
        }
        m_SystemRAM = memory.ram; // In MB.
        m_FreeSystemRAM = memory.free / (SystemInformation::MEGABYTE); // Returned in bytes, converted to MB.

        sigar_cpu_info_list_t cpuInfoList;
        if (sigar_cpu_info_list_get(m_pSigar, &cpuInfoList) != SIGAR_OK)
        {
            return false;
        }

        for (unsigned long i = 0; i < cpuInfoList.number; ++i)
        {
            sigar_cpu_info_t cpuInfo = cpuInfoList.data[i];
            m_CPUSpeed = cpuInfo.mhz; // Clock given in MHz.
            m_TotalCPUCores = cpuInfo.total_cores;
            m_CPUCache = cpuInfo.cache_size;
        }
        sigar_cpu_info_list_destroy(m_pSigar, &cpuInfoList);

        sigar_file_system_list_t fileSystemList;
        if (sigar_file_system_list_get(m_pSigar, &fileSystemList) != SIGAR_OK)
        {
            return false;
        }

        for (unsigned long i = 0; i < fileSystemList.number; ++i)
        {
            sigar_file_system_t fileSystem = fileSystemList.data[i];

            sigar_file_system_usage_t fileSystemUsage;
            if (sigar_file_system_usage_get(m_pSigar, fileSystem.dir_name, &fileSystemUsage) != SIGAR_OK)
            {
                // If we can't retrieve the usage, we skip the file system.
                continue;
            }

            m_DiskNameVector.push_back(fileSystem.dir_name);
            m_DiskSpaceVector.push_back(fileSystemUsage.total);
            m_FreeDiskSpaceVector.push_back(fileSystemUsage.free);
        }
        sigar_file_system_list_destroy(m_pSigar, &fileSystemList);

        return true;
    }

    bool SystemInformation::Destroy()
    {
        if (m_pSigar != nullptr)
        {
            sigar_close(m_pSigar);
            m_pSigar = nullptr;
        }

        m_CPUSpeed = 0;
        m_TotalCPUCores = 0;
        m_CPUCache = 0;

        m_SystemRAM = 0;
        m_FreeSystemRAM = 0;

        m_DiskNameVector.clear();
        m_DiskSpaceVector.clear();
        m_FreeDiskSpaceVector.clear();

        return true;
    }

    const unsigned long long SystemInformation::GetCPUSpeedInMHz() const
    {
        return m_CPUSpeed;
    }

    const unsigned int SystemInformation::GetTotalCPUCores() const
    {
        return m_TotalCPUCores;
    }

    const unsigned long long SystemInformation::GetSystemRAMInMB() const
    {
        return m_SystemRAM;
    }

    const unsigned long long SystemInformation::GetAvailableSystemRAMInMB() const
    {
        return m_FreeSystemRAM;
    }

    const std::vector<std::string>& SystemInformation::GetDiskNames() const
    {
        return m_DiskNameVector;
    }

    const std::vector<unsigned long long>& SystemInformation::GetTotalDiskSpaceInBytes() const
    {
        return m_DiskSpaceVector;
    }

    const std::vector<unsigned long long>& SystemInformation::GetFreeDiskSpaceInBytes() const
    {
        return m_FreeDiskSpaceVector;
    }

}
