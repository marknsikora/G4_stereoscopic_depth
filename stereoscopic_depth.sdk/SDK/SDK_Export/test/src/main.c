/*
 * main.c
 *
 *  Created on: Mar 4, 2015
 *      Author: msikora
 */

#define DEBUG 1
#undef NDEBUG

#include <assert.h>
#include <string.h>

#include "xparameters.h"

#include "xil_printf.h"

#include "xaxivdma.h"

#define QVGA_VERTICAL 240
#define QVGA_HORIZONTAL (320*3)
#define QVGA_SIZE (QVGA_VERTICAL*QVGA_HORIZONTAL)

#define FRAME_VERTICAL 480
#define FRAME_HORIZONTAL (640*3)
#define FRAME_SIZE (FRAME_VERTICAL*FRAME_HORIZONTAL)

char frame_buffer[4][FRAME_SIZE];

void assert_handler(const char *File, int Line)
{
	xil_printf("Assertion failed on line %d in '%s'.\n", Line, File);
}

u32 vdma_status_dump(XAxiVdma *InstancePtr, u16 Direction)
{
	u32 status = XAxiVdma_GetStatus(InstancePtr, Direction);

	if (Direction == XAXIVDMA_READ) xil_printf("READ\n");
	if (Direction == XAXIVDMA_WRITE) xil_printf("WRITE\n");

	if (status & XAXIVDMA_SR_HALTED_MASK) xil_printf("halted\n"); else xil_printf("running\n");
	if (status & XAXIVDMA_SR_IDLE_MASK) xil_printf("idle\n");
	if (status & XAXIVDMA_SR_ERR_INTERNAL_MASK) xil_printf("internal err\n");
	if (status & XAXIVDMA_SR_ERR_SLAVE_MASK) xil_printf("slave err\n");
	if (status & XAXIVDMA_SR_ERR_DECODE_MASK) xil_printf("decode err\n");
	if (status & XAXIVDMA_SR_ERR_FSZ_LESS_MASK) xil_printf("FSize Less Mismatch err\n");
	if (status & XAXIVDMA_SR_ERR_LSZ_LESS_MASK) xil_printf("LSize Less Mismatch err\n");
	if (status & XAXIVDMA_SR_ERR_SG_SLV_MASK) xil_printf("SG slave err\n");
	if (status & XAXIVDMA_SR_ERR_SG_DEC_MASK) xil_printf("SG decode err\n");
	if (status & XAXIVDMA_SR_ERR_FSZ_MORE_MASK) xil_printf("FSize More Mismatch err\n");

	return status;
}

int init_vdma(XAxiVdma *vdma, u16 DeviceId)
{
	int ret;

	XAxiVdma_Config *cfg;

	cfg = XAxiVdma_LookupConfig(DeviceId);
	ret = XAxiVdma_CfgInitialize(vdma, cfg, cfg->BaseAddress);
	Xil_AssertNonvoid(ret==XST_SUCCESS);

	if (vdma->HasMm2S) {
		XAxiVdma_Reset(vdma, XAXIVDMA_READ);
		while (XAxiVdma_ResetNotDone(vdma, XAXIVDMA_READ))
			;

		ret = XAxiVdma_ClearDmaChannelErrors(vdma, XAXIVDMA_READ, XAXIVDMA_SR_ERR_ALL_MASK);
		Xil_AssertNonvoid(ret==XST_SUCCESS);
	}

	if (vdma->HasS2Mm) {
		XAxiVdma_Reset(vdma, XAXIVDMA_WRITE);
		while (XAxiVdma_ResetNotDone(vdma, XAXIVDMA_WRITE))
			;

		ret = XAxiVdma_ClearDmaChannelErrors(vdma, XAXIVDMA_WRITE, XAXIVDMA_SR_ERR_ALL_MASK);
		Xil_AssertNonvoid(ret==XST_SUCCESS);
	}

	return XST_SUCCESS;
}

int main(void)
{
	int i;
	int ret;
	XAxiVdma vdma_1, vdma_2, vdma_3;
	XAxiVdma_DmaSetup writeCfg_1, writeCfg_2, writeCfg_3;
	XAxiVdma_DmaSetup readCfg_1, readCfg_2, readCfg_3;

	Xil_AssertSetCallback(assert_handler);

	xil_printf("init...\n");

	// Clear memory
	for (i = 0; i < XPAR_AXI_VDMA_0_NUM_FSTORES; i++) {
		memset(frame_buffer[i], 0, FRAME_SIZE);
		xil_printf("%x\n", frame_buffer[i]);
	}

	// Initialize VDMA
	xil_printf("start:\tvdma init\n");
	init_vdma(&vdma_1, XPAR_AXI_VDMA_0_DEVICE_ID);
	init_vdma(&vdma_2, XPAR_AXI_VDMA_1_DEVICE_ID);
	init_vdma(&vdma_3, XPAR_AXI_VDMA_2_DEVICE_ID);
	xil_printf("start:\tvdma init\n");

	// Configure read and write channels
	xil_printf("start:\tvdma channels\n");
	memset(&writeCfg_1, 0, sizeof(XAxiVdma_DmaSetup));
	writeCfg_1.VertSizeInput = QVGA_VERTICAL;
	writeCfg_1.HoriSizeInput = QVGA_HORIZONTAL;
	writeCfg_1.Stride = FRAME_HORIZONTAL;
	writeCfg_1.FrameDelay = 0;
	writeCfg_1.EnableCircularBuf = 1;
	writeCfg_1.EnableSync = 0;
	writeCfg_1.PointNum = XPAR_AXI_VDMA_0_DEVICE_ID;
	writeCfg_1.EnableFrameCounter = 0;
	writeCfg_1.FixedFrameStoreAddr = 0;
	writeCfg_1.GenLockRepeat = 0;
	ret = XAxiVdma_DmaConfig(&vdma_1, XAXIVDMA_WRITE, &writeCfg_1);
	Xil_AssertNonvoid(ret==XST_SUCCESS);
	for (i = 0; i < vdma_1.WriteChannel.NumFrames; i++) {
		writeCfg_1.FrameStoreStartAddr[i] = frame_buffer[i];
	}
	ret = XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_WRITE, writeCfg_1.FrameStoreStartAddr);
	Xil_AssertNonvoid(ret==XST_SUCCESS);

	memset(&readCfg_1, 0, sizeof(XAxiVdma_DmaSetup));
	readCfg_1.VertSizeInput = QVGA_VERTICAL;
	readCfg_1.HoriSizeInput = QVGA_HORIZONTAL;
	readCfg_1.Stride = FRAME_HORIZONTAL;
	readCfg_1.FrameDelay = 1;
	readCfg_1.EnableCircularBuf = 1;
	readCfg_1.EnableSync = 0;
	readCfg_1.PointNum = XPAR_AXI_VDMA_0_DEVICE_ID;
	readCfg_1.EnableFrameCounter = 0;
	readCfg_1.FixedFrameStoreAddr = 0;
	readCfg_1.GenLockRepeat = 0;
	ret = XAxiVdma_DmaConfig(&vdma_1, XAXIVDMA_READ, &readCfg_1);
	Xil_AssertNonvoid(ret==XST_SUCCESS);
	for (i = 0; i < vdma_1.ReadChannel.NumFrames; i++) {
		readCfg_1.FrameStoreStartAddr[i] = frame_buffer[i];
	}
	ret = XAxiVdma_DmaSetBufferAddr(&vdma_1, XAXIVDMA_READ, readCfg_1.FrameStoreStartAddr);
	Xil_AssertNonvoid(ret==XST_SUCCESS);

	memset(&writeCfg_2, 0, sizeof(XAxiVdma_DmaSetup));
	writeCfg_2.VertSizeInput = QVGA_VERTICAL;
	writeCfg_2.HoriSizeInput = QVGA_HORIZONTAL;
	writeCfg_2.Stride = FRAME_HORIZONTAL;
	writeCfg_2.FrameDelay = 0;
	writeCfg_2.EnableCircularBuf = 1;
	writeCfg_2.EnableSync = 0;
	writeCfg_2.PointNum = XPAR_AXI_VDMA_1_DEVICE_ID;
	writeCfg_2.EnableFrameCounter = 0;
	writeCfg_2.FixedFrameStoreAddr = 0;
	writeCfg_2.GenLockRepeat = 0;
	ret = XAxiVdma_DmaConfig(&vdma_2, XAXIVDMA_WRITE, &writeCfg_2);
	Xil_AssertNonvoid(ret==XST_SUCCESS);
	for (i = 0; i < vdma_2.WriteChannel.NumFrames; i++) {
		writeCfg_2.FrameStoreStartAddr[i] = frame_buffer[i] + QVGA_HORIZONTAL;
	}
	ret = XAxiVdma_DmaSetBufferAddr(&vdma_2, XAXIVDMA_WRITE, writeCfg_2.FrameStoreStartAddr);
	Xil_AssertNonvoid(ret==XST_SUCCESS);

	memset(&readCfg_2, 0, sizeof(XAxiVdma_DmaSetup));
	readCfg_2.VertSizeInput = QVGA_VERTICAL;
	readCfg_2.HoriSizeInput = QVGA_HORIZONTAL;
	readCfg_2.Stride = FRAME_HORIZONTAL;
	readCfg_2.FrameDelay = 1;
	readCfg_2.EnableCircularBuf = 1;
	readCfg_2.EnableSync = 0;
	readCfg_2.PointNum = XPAR_AXI_VDMA_1_DEVICE_ID;
	readCfg_2.EnableFrameCounter = 0;
	readCfg_2.FixedFrameStoreAddr = 0;
	readCfg_2.GenLockRepeat = 0;
	ret = XAxiVdma_DmaConfig(&vdma_2, XAXIVDMA_READ, &readCfg_2);
	Xil_AssertNonvoid(ret==XST_SUCCESS);
	for (i = 0; i < vdma_2.ReadChannel.NumFrames; i++) {
		readCfg_2.FrameStoreStartAddr[i] = frame_buffer[i] + QVGA_HORIZONTAL;
	}
	ret = XAxiVdma_DmaSetBufferAddr(&vdma_2, XAXIVDMA_READ, readCfg_2.FrameStoreStartAddr);
	Xil_AssertNonvoid(ret==XST_SUCCESS);

	memset(&writeCfg_3, 0, sizeof(XAxiVdma_DmaSetup));
	writeCfg_3.VertSizeInput = QVGA_VERTICAL;
	writeCfg_3.HoriSizeInput = QVGA_HORIZONTAL;
	writeCfg_3.Stride = FRAME_HORIZONTAL;
	writeCfg_3.FrameDelay = 0;
	writeCfg_3.EnableCircularBuf = 1;
	writeCfg_3.EnableSync = 0;
	writeCfg_3.PointNum = XPAR_AXI_VDMA_2_DEVICE_ID;
	writeCfg_3.EnableFrameCounter = 0;
	writeCfg_3.FixedFrameStoreAddr = 0;
	writeCfg_3.GenLockRepeat = 0;
	ret = XAxiVdma_DmaConfig(&vdma_3, XAXIVDMA_WRITE, &writeCfg_3);
	Xil_AssertNonvoid(ret==XST_SUCCESS);
	for (i = 0; i < vdma_3.WriteChannel.NumFrames; i++) {
		writeCfg_3.FrameStoreStartAddr[i] = frame_buffer[i] + QVGA_VERTICAL*FRAME_HORIZONTAL;
	}
	ret = XAxiVdma_DmaSetBufferAddr(&vdma_3, XAXIVDMA_WRITE, writeCfg_3.FrameStoreStartAddr);
	Xil_AssertNonvoid(ret==XST_SUCCESS);

	memset(&readCfg_3, 0, sizeof(XAxiVdma_DmaSetup));
	readCfg_3.VertSizeInput = FRAME_VERTICAL;
	readCfg_3.HoriSizeInput = FRAME_HORIZONTAL;
	readCfg_3.Stride = FRAME_HORIZONTAL;
	readCfg_3.FrameDelay = 1;
	readCfg_3.EnableCircularBuf = 1;
	readCfg_3.EnableSync = 0;
	readCfg_3.PointNum = XPAR_AXI_VDMA_2_DEVICE_ID;
	readCfg_3.EnableFrameCounter = 0;
	readCfg_3.FixedFrameStoreAddr = 0;
	readCfg_3.GenLockRepeat = 0;
	ret = XAxiVdma_DmaConfig(&vdma_3, XAXIVDMA_READ, &readCfg_3);
	Xil_AssertNonvoid(ret==XST_SUCCESS);
	for (i = 0; i < vdma_3.ReadChannel.NumFrames; i++) {
		readCfg_3.FrameStoreStartAddr[i] = frame_buffer[i];
	}
	ret = XAxiVdma_DmaSetBufferAddr(&vdma_3, XAXIVDMA_READ, readCfg_3.FrameStoreStartAddr);
	Xil_AssertNonvoid(ret==XST_SUCCESS);

	xil_printf("end:\tvdma channels\n");

	// Start VDMA transfer
	xil_printf("start:\tvdma start\n");

	ret = XAxiVdma_DmaStart(&vdma_3, XAXIVDMA_READ);
	Xil_AssertNonvoid(ret==XST_SUCCESS);

	ret = XAxiVdma_DmaStart(&vdma_1, XAXIVDMA_READ);
	Xil_AssertNonvoid(ret==XST_SUCCESS);
	ret = XAxiVdma_DmaStart(&vdma_2, XAXIVDMA_READ);
	Xil_AssertNonvoid(ret==XST_SUCCESS);

	ret = XAxiVdma_DmaStart(&vdma_1, XAXIVDMA_WRITE);
	Xil_AssertNonvoid(ret==XST_SUCCESS);
	ret = XAxiVdma_DmaStart(&vdma_2, XAXIVDMA_WRITE);
	Xil_AssertNonvoid(ret==XST_SUCCESS);

	ret = XAxiVdma_DmaStart(&vdma_3, XAXIVDMA_WRITE);
	Xil_AssertNonvoid(ret==XST_SUCCESS);

	xil_printf("end:\tvdma start\n");

	xil_printf("start:\tcomparator\n");
	(*(volatile u32 *)((0x44A30000)) = (0x1));
	xil_printf("end:\tcomparator\n");

	while (1) {
		for (i = 0; i < 200000; i++)
			;

		xil_printf("\n");

		vdma_status_dump(&vdma_1, XAXIVDMA_WRITE);
		vdma_status_dump(&vdma_2, XAXIVDMA_WRITE);
		vdma_status_dump(&vdma_3, XAXIVDMA_WRITE);
		vdma_status_dump(&vdma_1, XAXIVDMA_READ);
		vdma_status_dump(&vdma_2, XAXIVDMA_READ);
		vdma_status_dump(&vdma_3, XAXIVDMA_READ);

		ret = XAxiVdma_ClearDmaChannelErrors(&vdma_1, XAXIVDMA_WRITE, XAXIVDMA_SR_ERR_ALL_MASK);
		//Xil_AssertNonvoid(ret==XST_SUCCESS);
		ret = XAxiVdma_ClearDmaChannelErrors(&vdma_2, XAXIVDMA_WRITE, XAXIVDMA_SR_ERR_ALL_MASK);
		//Xil_AssertNonvoid(ret==XST_SUCCESS);
		ret = XAxiVdma_ClearDmaChannelErrors(&vdma_3, XAXIVDMA_WRITE, XAXIVDMA_SR_ERR_ALL_MASK);
		//Xil_AssertNonvoid(ret==XST_SUCCESS);

		ret = XAxiVdma_ClearDmaChannelErrors(&vdma_1, XAXIVDMA_READ, XAXIVDMA_SR_ERR_ALL_MASK);
		//Xil_AssertNonvoid(ret==XST_SUCCESS);
		ret = XAxiVdma_ClearDmaChannelErrors(&vdma_2, XAXIVDMA_READ, XAXIVDMA_SR_ERR_ALL_MASK);
		//Xil_AssertNonvoid(ret==XST_SUCCESS);
		ret = XAxiVdma_ClearDmaChannelErrors(&vdma_3, XAXIVDMA_READ, XAXIVDMA_SR_ERR_ALL_MASK);
		//Xil_AssertNonvoid(ret==XST_SUCCESS);
	}

	return 0;
}
