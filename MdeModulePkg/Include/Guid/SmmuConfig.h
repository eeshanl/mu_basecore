/** @file
    File for SMMU config structures.

    Copyright (C) Microsoft Corporation. All rights reserved.
    SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef _SMMU_CONFIG_GUID_H_
#define _SMMU_CONFIG_GUID_H_

#include <IndustryStandard/IoRemappingTable.h>

typedef struct _SBSA_EFI_ACPI_6_0_IO_REMAPPING_ITS_NODE {
  EFI_ACPI_6_0_IO_REMAPPING_ITS_NODE    Node;
  UINT32                                Identifiers;
} SBSA_EFI_ACPI_6_0_IO_REMAPPING_ITS_NODE;

typedef struct _SBSA_EFI_ACPI_6_0_IO_REMAPPING_SMMU3_NODE {
  EFI_ACPI_6_0_IO_REMAPPING_SMMU3_NODE    SmmuNode;
  EFI_ACPI_6_0_IO_REMAPPING_ID_TABLE      SmmuIdMap;
} SBSA_EFI_ACPI_6_0_IO_REMAPPING_SMMU3_NODE;

typedef struct _SBSA_EFI_ACPI_6_0_IO_REMAPPING_RC_NODE{
  EFI_ACPI_6_0_IO_REMAPPING_RC_NODE     RcNode;
  EFI_ACPI_6_0_IO_REMAPPING_ID_TABLE    RcIdMap;
} SBSA_EFI_ACPI_6_0_IO_REMAPPING_RC_NODE;

typedef struct _SBSA_IO_REMAPPING_STRUCTURE{
  EFI_ACPI_6_0_IO_REMAPPING_TABLE              Iort;
  SBSA_EFI_ACPI_6_0_IO_REMAPPING_ITS_NODE      ItsNode;
  SBSA_EFI_ACPI_6_0_IO_REMAPPING_SMMU3_NODE    SmmuNode;
  SBSA_EFI_ACPI_6_0_IO_REMAPPING_RC_NODE       RcNode;
} SBSA_IO_REMAPPING_STRUCTURE;

typedef struct _SMMU_CONFIG {
  SBSA_IO_REMAPPING_STRUCTURE Config;
} SMMU_CONFIG;

extern EFI_GUID gEfiSmmuConfigGuid;

#endif
