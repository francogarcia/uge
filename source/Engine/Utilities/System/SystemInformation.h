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

#pragma once

namespace uge
{

    class SystemInformation
    {
    public:
        /// Defines the size of one kilobyte.
        static const unsigned int KILOBYTE = 1024;
        /// Defines the size of one megabyte.
        static const unsigned int MEGABYTE = KILOBYTE * KILOBYTE;
        /// Defines the size of one gigabyte.
        static const unsigned int GIGABYTE = MEGABYTE * KILOBYTE;

        /**
         *  Constructor.
         */
        SystemInformation();

        /**
         *  Destructor.
         */
        ~SystemInformation();

        /**
         *  Initializes the object and gathers the system information.
         * @return : true if sucessful; false otherwise.
         */
        bool Init();

        /**
         *  Destroys the object.
         * @return : true if sucessful; false otherwise.
         */
        bool Destroy();

        /**
         *  Retrieves the speed of the machine's CPU.
         * @return : the speed of the CPU, in MHz.
         */
        const unsigned long long GetCPUSpeedInMHz() const;

        /**
         *  Retrieves the number of CPU cores in the machine.
         * @return : the total number of CPU cores available in the machine.
         */
        const unsigned int GetTotalCPUCores() const;

        /**
         *  Retrieves the size of the machine's physical RAM.
         * @return : the size of the RAM, in MB.
         */
        const unsigned long long GetSystemRAMInMB() const;

        /**
         *  Retrieves the size of the machine's currently available physical RAM.
         * @return : the size of the free RAM, in MB.
         */
        const unsigned long long GetAvailableSystemRAMInMB() const;

        /**
         *  Retrieves the labels used to name the filesytem secondary disks.
         * @return : a vector containing all the names of the mounted secondary-memory devices.
         */
        const std::vector<std::string>& GetDiskNames() const;

        /**
         *  Retrieves the total space of the in each disks of the machine.
         * @return : a vector containing the total space on each secondary disk, in bytes.
         */
        const std::vector<unsigned long long>& GetTotalDiskSpaceInBytes() const;

        /**
         *  Retrieves the total free space of the in each disks of the machine.
         * @return : a vector containing the free space on each secondary disk, in bytes.
         */
        const std::vector<unsigned long long>& GetFreeDiskSpaceInBytes() const;

    private:
        /// 3rd party library used to retrieve the system information.
        sigar_t* m_pSigar;

        /// The speed of the CPU, in MHz.
        unsigned long long m_CPUSpeed;
        /// The number of cores of the CPU.
        unsigned int m_TotalCPUCores;
        /// Cache of the CPU.
        unsigned long long m_CPUCache;

        /// The total RAM of the system, in MB.
        unsigned long long m_SystemRAM;
        /// The total free RAM of the system, in MB.
        unsigned long long m_FreeSystemRAM;

        /// The name of the filesystems.
        std::vector<std::string> m_DiskNameVector;
        /// The total disk space, in bytes.
        std::vector<unsigned long long> m_DiskSpaceVector;
        /// The available disk space, in bytes.
        std::vector<unsigned long long> m_FreeDiskSpaceVector;
    };

}
