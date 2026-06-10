/** @file IoMmu.h

    This file is the IoMmu header file for SMMU driver.

    Copyright (c) Microsoft Corporation.
    SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef IOMMU_H_
#define IOMMU_H_

/**
  Page Table bit definitions used by the Smmu/IoMmu for mapping
  <https://developer.arm.com/documentation/102105/ka-07>
  Section D8.3.1 VMSAv8-64 descriptor formats (Stage 1)
**/
#define PAGE_TABLE_ENTRY_VALID_BIT  0x1
#define PAGE_TABLE_BLOCK_OFFSET     0xFFF
#define PAGE_TABLE_ACCESS_FLAG      (0x1 << 10)
#define PAGE_TABLE_DESCRIPTOR       (0x1 << 1)

//
// Stage 1 leaf descriptor lower attributes (VMSAv8-64). The data access
// memory type comes from the MAIR entry selected by AttrIndx (configured in
// the Context Descriptor), not from the descriptor itself.
//
#define PAGE_TABLE_ATTR_INDEX(Index)   (((UINT16)(Index) & 0x7) << 2)  // AttrIndx[2:0] -> MAIR index
#define PAGE_TABLE_S1_AP_READ_WRITE    (0x1 << 6)                      // AP[2:1]=0b01: read/write at EL0 and EL1
#define PAGE_TABLE_S1_AP_READ_ONLY     (0x3 << 6)                      // AP[2:1]=0b11: read-only
#define PAGE_TABLE_SH_NON_SHAREABLE    (0x0 << 8)
#define PAGE_TABLE_SH_OUTER_SHAREABLE  (0x2 << 8)
#define PAGE_TABLE_SH_INNER_SHAREABLE  (0x3 << 8)

//
// Stage 1 leaf descriptor flags granting full read/write access to identity-
// mapped DMA, using MAIR attribute index 0 (configured in the Context
// Descriptor). Shareability is inner-shareable; for Normal Non-Cacheable
// memory the field is ignored by the architecture.
//
#define PAGE_TABLE_S1_LEAF_RW_FLAGS \
  (PAGE_TABLE_S1_AP_READ_WRITE | PAGE_TABLE_ATTR_INDEX (0) | PAGE_TABLE_SH_INNER_SHAREABLE)

// Forward declaration; full definition lives in SmmuV3.h.
typedef struct _SMMU_INFO SMMU_INFO;

typedef UINT64 PAGE_TABLE_ENTRY;

#define PAGE_TABLE_SIZE  (EFI_PAGE_SIZE / sizeof(PAGE_TABLE_ENTRY))  // Number of entries in a page table

// Page Table Structure used by SMMU
typedef struct _PAGE_TABLE {
  PAGE_TABLE_ENTRY    Entries[PAGE_TABLE_SIZE];
} PAGE_TABLE;

/**
  Update the page table mapping with the given physical address and flags.

  @param [in]  SmmuInfo                   SMMU instance.
  @param [in]  Root                       Pointer to the root page table.
  @param [in]  Asid                       ASID for associated page table root.
  @param [in]  PhysicalAddress            Physical address to map.
  @param [in]  Bytes                      Number of bytes to map.
  @param [in]  Flags                      Flags to set for the mapping. 12 bits or less.
  @param [in]  Valid                      Boolean to indicate if the entry is valid.

  @retval EFI_SUCCESS            Success.
  @retval EFI_INVALID_PARAMETER  Invalid parameter.
  @retval EFI_OUT_OF_RESOURCES   Out of resources.
**/
EFI_STATUS
UpdatePageTable (
  IN SMMU_INFO   *SmmuInfo,
  IN PAGE_TABLE  *Root,
  IN UINT16      Asid,
  IN UINT64      PhysicalAddress,
  IN UINT64      Bytes,
  IN UINT16      Flags,
  IN BOOLEAN     Valid
  );

/**
  Installs the IOMMU Protocol on this SMMU instance.

  @retval EFI_SUCCESS           All the protocol interface was installed.
  @retval EFI_OUT_OF_RESOURCES  There was not enough memory in pool to install all the protocols.
  @retval EFI_ALREADY_STARTED   A Device Path Protocol instance was passed in that is already present in
                                the handle database.
  @retval EFI_INVALID_PARAMETER Handle is NULL.
  @retval EFI_INVALID_PARAMETER Protocol is already installed on the handle specified by Handle.
**/
EFI_STATUS
IoMmuInit (
  VOID
  );

#endif
