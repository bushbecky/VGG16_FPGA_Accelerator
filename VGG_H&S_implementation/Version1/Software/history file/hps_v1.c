///////////////////////////////////////
// DMA controller test
// Send data from HPS DDR3
// to FPGA On-chip Memory
// compile with
// gcc hps_v1.c -o hps_v1  -O3
//
// based on a design from
// https://github.com/robertofem/CycloneVSoC-examples/blob/master/Linux-applications/DMA_transfer_FPGA_DMAC
// & https://people.ece.cornell.edu/land/courses/ece5760/DE1_SOC/HPS_peripherials/FPGA_addr_index.html
//
// Author: Ke Xu
///////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/mman.h>
#include <sys/time.h> 
#include <linux/malloc.h>
#include <math.h> 

/* ----------------------------------*/
//#define H2F_AXI_MASTER_BASE    0xC0000000
#define F2H_SDRAM_MASTER_BASE  0x00100000
// On-chip Memory on FPGA
// main bus; scratch RAM
//#define FPGA_ONCHIP_BASE       0xC0001000
#define FPGA_ONCHIP_BASE       0xC8000000
#define FPGA_ONCHIP_SPAN       0x00001000
// h2f bus
// RAM FPGA port s2
// main bus address 0x0000_1000
volatile unsigned int * ocpram_ptr = NULL;   //ocpram = on-chip-ram; ptr = pointer
void *oncpram_virtual_base;

/* ----------------------------------*/
// axi_lw_bus; DMA address
#define HW_REGS_BASE           0xff200000
#define HW_REGS_SPAN           0x00005000
#define DMA0                   0x00000000   //This address needs to be confirmed!!!!
#define DMA1                   0x00000020
#define DMA_STATUS_OFFSET      0x00
#define DMA_READ_ADDR_OFFSET   0x04         //NOTE: DATASHEET says 1 for this addr
#define DMA_WRTE_ADDR_OFFSET   0x08
#define DMA_LENGTH_OFFSET      0x012
#define DMA_CNTL_OFFSET        0x024
// h2f_axi_lw_bus base
void *h2f_lw_virtual_base;
// HPS_TO_FPGA DMA0 address = 0
volatile unsigned int * DMA0_status_ptr = NULL;
volatile unsigned int * DMA0_read_ptr   = NULL;
volatile unsigned int * DMA0_write_ptr  = NULL;
volatile unsigned int * DMA0_length_ptr = NULL;
volatile unsigned int * DMA0_cntl_ptr   = NULL;
// HPS_TO_FPGA DMA1 address = 0
volatile unsigned int * DMA1_status_ptr = NULL;
volatile unsigned int * DMA1_read_ptr   = NULL;
volatile unsigned int * DMA1_write_ptr  = NULL;
volatile unsigned int * DMA1_length_ptr = NULL;
volatile unsigned int * DMA1_cntl_ptr   = NULL;

/* ----------------------------------*/
// HPS DDR3 base and span
#define HPS_DDR3_BASE          0x00000000
#define HPS_DDR3_SPAN          0x3fffffff
#define HPS_DDR3_SIZE          200*1024*1024        //200 
// HPS DDR3 memory
volatile unsigned int *hps_ddr3_ptr = NULL;
void *hps_ddr3_virtual_base;

// WAIT looks nicer than just braces
#define WAIT {}

int fd;

int main(void) {
    // Declare volatile pointers to I/O registers (volatile 	
	// means that IO load and store instructions will be used 	
	// to access these pointer locations, 
	// instead of regular memory loads and stores)

    /* ----------------------------------*/
    // get FPGA address
    if ((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
        printf("ERROR: could not open \"/dev/mem\"...\n");
        return 1;
    }
    printf("Open /dev/mem successful\n");

    /* ----------------------------------*/
    // Get virtual address which maps to physical for 
    // axi_lw_master bus
    // DMA status register
    h2f_lw_virtual_base = mmap(NULL, HW_REGS_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, HW_REGS_BASE);
    
    if (h2f_lw_virtual_base == MAP_FAILED) {
        printf("ERROR: mmap(h2p_lw) failed ...\n");
        close(fd);
        return 1;
    }
    //DMA0 registers address shift to physical address
    DMA0_status_ptr = (unsigned int *) (h2f_lw_virtual_base);
    DMA0_read_ptr   = (unsigned int *) (h2f_lw_virtual_base + DMA_READ_ADDR_OFFSET);
    DMA0_write_ptr  = (unsigned int *) (h2f_lw_virtual_base + DMA_WRTE_ADDR_OFFSET);
    DMA0_length_ptr = (unsigned int *) (h2f_lw_virtual_base + DMA_LENGTH_OFFSET);
    DMA0_cntl_ptr   = (unsigned int *) (h2f_lw_virtual_base + DMA_CNTL_OFFSET);
    //DMA registers address shift to physical address
    DMA1_status_ptr = (unsigned int *) (h2f_lw_virtual_base                        + DMA1);
    DMA1_read_ptr   = (unsigned int *) (h2f_lw_virtual_base + DMA_READ_ADDR_OFFSET + DMA1);
    DMA1_write_ptr  = (unsigned int *) (h2f_lw_virtual_base + DMA_WRTE_ADDR_OFFSET + DMA1);
    DMA1_length_ptr = (unsigned int *) (h2f_lw_virtual_base + DMA_LENGTH_OFFSET    + DMA1);
    DMA1_cntl_ptr   = (unsigned int *) (h2f_lw_virtual_base + DMA_CNTL_OFFSET      + DMA1);
    printf("Address allocating for DMA0 & DMA1 successful");
    /* ----------------------------------*/
    // FPGA on-chip memory s2 port
    //ocpram_virtual_base = mmap(NULL, FPGA_ONCHIP_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, FPGA_ONCHIP_BASE);
    // ... search in hps_origin.c



    /* ----------------------------------*/
    // Get HPS DDR3 address
    // 
    //dma_addr_t hps_ddr3_base;
    // struct device *dev: no idea what is it!!!!!
    // size_t size: unit is byte
    // dma_handle: acquire bus address in ARM, need changing to phys by virt_to_phys()
    // flag: GFP_KERNEL; GFP_ATOMIC;
    // void * dma_alloc_coherent(struct device *dev, size_t size (byte), dma_addr_t *dma_handle, gfp_t flag)  
    //hps_ddr3_ptr = dma_alloc_coherent(NULL, HPS_DDR3_SIZE, hps_ddr3_base, GFP_ATOMIC);
    // change virtual address to physical one of DDR3
    //unsigned * int hps_ddr3_phys = virt_to_phys(hps_ddr3_base);

    hps_ddr3_ptr = kmalloc(128, GFP_ATOMIC);

     
    //printf("Address allocating for HPS_DDR3 successful\n");
    /* ----------------------------------*/
    // Program write data to DDR3
    // DMA0 read from DDR3 then write to FPGA On-chip memory
    // Program read FPGA

    // Write data into DDR3 
    *hps_ddr3_ptr = 250;
    printf("Write data into HPS_DDR3 successful\n");
    int temp = 0;
    temp = *(hps_ddr3_ptr);
    printf("Data at addr:0x0000_0000 in DDR3 is: %d\n", temp);

    // DMA0 transfer from HPS_DDR3->FPGA_On_chip_memory
    // set up DMA0
    // from https://www.intel.com/content/dam/www/programmable/us/en/pdfs/literature/ug/ug_embedded_ip.pdf
    // version: 19.1
    // section 29.4.3: Table 283: Control Regesiter bits
    *(DMA0_status_ptr) = 0;
    // read bus_master gets data from HPS DDR3 addr = 0x0000_0000, setted by Qsys
    *(DMA0_status_ptr + 1) = &hps_ddr3_ptr;
    // write bus_master for FPGA on-chip memory is mapped to 0x0001_0000, setted by Qsys
    *(DMA0_status_ptr + 2) = 0x08000000;
    // 1 word = 4 bytes
    *(DMA0_status_ptr + 3) = 4;
    // From table 283:
    // set bit 2 for WORD transfer
	// set bit 3 to start DMA0
	// set bit 7 to stop on byte-count
    *(DMA0_status_ptr + 6) = 0b10001100;
    while ((*(DMA0_status_ptr) & 0x010) == 0) {
        WAIT;
    }
    printf("DMA0 finish writing from DDR3 into FPGA on-chip Memory\n");

    /* ----------------------------------*/
    // DMA1 read from FPGA On-chip memory then write to DDR3 
    // Program read from DDR3
    *(DMA1_status_ptr) = 0;
    // read bus_master gets data from FPGA on-chip Memory = 0x0000_1000, setted by Qsys
    *(DMA1_status_ptr + 1) = 0x08000000;
    // write bus_master for FPGA on-chip memory is mapped to 0x0000_0010, setted by Qsys
    *(DMA1_status_ptr + 2) = &hps_ddr3_ptr + 1;
    // 1 word = 4 bytes
    *(DMA1_status_ptr + 3) = 4;
    // From table 283:
    // set bit 2 for WORD transfer
	// set bit 3 to start DMA1
	// set bit 7 to stop on byte-count
    *(DMA1_status_ptr + 6) = 0b10001100;
    while ((*(DMA1_status_ptr) & 0x010) == 0) {
        WAIT;
    }
    printf("DMA1 finish writing from FPGA on-chip Memory into DDR3\n");

    // Read from DDR3 
    
    temp = *(hps_ddr3_ptr + 1);
    printf("Data at addr:0x0000_0010 in DDR3 is: %d\n", temp);

}
