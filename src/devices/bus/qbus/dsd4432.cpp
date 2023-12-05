// license:BSD-3-Clause
// copyright-holders:AJR
/**********************************************************************

    Data Systems Design A4432 Floppy Disk Interface

    This is an LSI-11 compatible, DMA-capable interface board for the
    DSD 440, an RX02-like floppy disk system from Data Systems
    Design (later known as Qualogy). The serial interface to the drive
    controller board might be logically compatible with DEC's own
    interfaces, though the 26-pin connector is not. PDP-11 (Unibus)
    and PDP-8 (Omnibus) interfaces were also available for the DSD 440;
    these were numbered 4430 and 2131 respectively.

    Currently this is a skeleton device with no real emulation. The
    DSD 440 controller itself has its own ROMs, 8085A CPU and Am2911
    bitslice sequencer.

**********************************************************************/

#include "emu.h"
#include "dsd4432.h"

// device type definition
DEFINE_DEVICE_TYPE(DSD4432, dsd4432_device, "dsd4432", "DSD A4432 Floppy Disk Interface")

dsd4432_device::dsd4432_device(const machine_config &mconfig, const char *tag, device_t *owner, u32 clock)
	: device_t(mconfig, DSD4432, tag, owner, clock)
	, device_qbus_card_interface(mconfig, *this)
	, m_bootstrap(*this, "bootstrap")
	, m_bootaddr(*this, "BOOT")
	, m_iv(*this, "IV")
	, m_mode(*this, "MODE")
{
}

void dsd4432_device::device_start()
{
	// ADI = A2, ADH = A3, ADG = A4, ADF = HI ROM, ADE = A5, ADD = A6, ADC = A7, ADB = A8, ADA = A1
	u16 *romdata = &m_bootstrap[0];
	const std::vector<u16> origdata(&romdata[0], &romdata[01000]);
	for (offs_t addr = 0; addr < 01000; addr++)
		romdata[addr] = origdata[bitswap<9>(addr, 1, 2, 3, 8, 4, 5, 6, 7, 0)];
}

static INPUT_PORTS_START(dsd4432)
	PORT_START("BOOT")
	PORT_DIPNAME(020, 020, "Bootstrap PROM") PORT_DIPLOCATION("5F:8") // Position is marked "DBST"
	PORT_DIPSETTING(000, DEF_STR(Off))
	PORT_DIPSETTING(020, DEF_STR(On))
	PORT_DIPNAME(014, 000, "Bootstrap PROM Address") PORT_DIPLOCATION("6B:1,2") // Positions are marked B-2 and B-1 and numbered 4 and 3 in manual
	PORT_DIPSETTING(014, "166000")
	PORT_DIPSETTING(010, "171000")
	PORT_DIPSETTING(000, "173000")
	PORT_DIPSETTING(004, "175000")
	PORT_DIPNAME(003, 000, "Starting Register Address") PORT_DIPLOCATION("6B:4,3") // Positions are marked A-2 and A-1 and numbered 1 and 2 in manual
	PORT_DIPSETTING(002, "177140")
	PORT_DIPSETTING(003, "177150")
	PORT_DIPSETTING(001, "177160")
	PORT_DIPSETTING(000, "177170")

	PORT_START("IV")
	PORT_DIPNAME(0774, 0264, "Interrupt Vector") PORT_DIPLOCATION("5F:1,2,3,4,5,6,7") // Positions are marked "IV2" to "IV8"
	PORT_DIPSETTING(0000, "000")
	PORT_DIPSETTING(0004, "004")
	PORT_DIPSETTING(0010, "010")
	PORT_DIPSETTING(0014, "014")
	PORT_DIPSETTING(0020, "020")
	PORT_DIPSETTING(0024, "024")
	PORT_DIPSETTING(0030, "030")
	PORT_DIPSETTING(0034, "034")
	PORT_DIPSETTING(0040, "040")
	PORT_DIPSETTING(0044, "044")
	PORT_DIPSETTING(0050, "050")
	PORT_DIPSETTING(0054, "054")
	PORT_DIPSETTING(0060, "060")
	PORT_DIPSETTING(0064, "064")
	PORT_DIPSETTING(0070, "070")
	PORT_DIPSETTING(0074, "074")
	PORT_DIPSETTING(0100, "100")
	PORT_DIPSETTING(0104, "104")
	PORT_DIPSETTING(0110, "110")
	PORT_DIPSETTING(0114, "114")
	PORT_DIPSETTING(0120, "120")
	PORT_DIPSETTING(0124, "124")
	PORT_DIPSETTING(0130, "130")
	PORT_DIPSETTING(0134, "134")
	PORT_DIPSETTING(0140, "140")
	PORT_DIPSETTING(0144, "144")
	PORT_DIPSETTING(0150, "150")
	PORT_DIPSETTING(0154, "154")
	PORT_DIPSETTING(0160, "160")
	PORT_DIPSETTING(0164, "164")
	PORT_DIPSETTING(0170, "170")
	PORT_DIPSETTING(0174, "174")
	PORT_DIPSETTING(0200, "200")
	PORT_DIPSETTING(0204, "204")
	PORT_DIPSETTING(0210, "210")
	PORT_DIPSETTING(0214, "214")
	PORT_DIPSETTING(0220, "220")
	PORT_DIPSETTING(0224, "224")
	PORT_DIPSETTING(0230, "230")
	PORT_DIPSETTING(0234, "234")
	PORT_DIPSETTING(0240, "240")
	PORT_DIPSETTING(0244, "244")
	PORT_DIPSETTING(0250, "250")
	PORT_DIPSETTING(0254, "254")
	PORT_DIPSETTING(0260, "260")
	PORT_DIPSETTING(0264, "264")
	PORT_DIPSETTING(0270, "270")
	PORT_DIPSETTING(0274, "274")
	PORT_DIPSETTING(0300, "300")
	PORT_DIPSETTING(0304, "304")
	PORT_DIPSETTING(0310, "310")
	PORT_DIPSETTING(0314, "314")
	PORT_DIPSETTING(0320, "320")
	PORT_DIPSETTING(0324, "324")
	PORT_DIPSETTING(0330, "330")
	PORT_DIPSETTING(0334, "334")
	PORT_DIPSETTING(0340, "340")
	PORT_DIPSETTING(0344, "344")
	PORT_DIPSETTING(0350, "350")
	PORT_DIPSETTING(0354, "354")
	PORT_DIPSETTING(0360, "360")
	PORT_DIPSETTING(0364, "364")
	PORT_DIPSETTING(0370, "370")
	PORT_DIPSETTING(0374, "374")
	PORT_DIPSETTING(0400, "400")
	PORT_DIPSETTING(0404, "404")
	PORT_DIPSETTING(0410, "410")
	PORT_DIPSETTING(0414, "414")
	PORT_DIPSETTING(0420, "420")
	PORT_DIPSETTING(0424, "424")
	PORT_DIPSETTING(0430, "430")
	PORT_DIPSETTING(0434, "434")
	PORT_DIPSETTING(0440, "440")
	PORT_DIPSETTING(0444, "444")
	PORT_DIPSETTING(0450, "450")
	PORT_DIPSETTING(0454, "454")
	PORT_DIPSETTING(0460, "460")
	PORT_DIPSETTING(0464, "464")
	PORT_DIPSETTING(0470, "470")
	PORT_DIPSETTING(0474, "474")
	PORT_DIPSETTING(0500, "500")
	PORT_DIPSETTING(0504, "504")
	PORT_DIPSETTING(0510, "510")
	PORT_DIPSETTING(0514, "514")
	PORT_DIPSETTING(0520, "520")
	PORT_DIPSETTING(0524, "524")
	PORT_DIPSETTING(0530, "530")
	PORT_DIPSETTING(0534, "534")
	PORT_DIPSETTING(0540, "540")
	PORT_DIPSETTING(0544, "544")
	PORT_DIPSETTING(0550, "550")
	PORT_DIPSETTING(0554, "554")
	PORT_DIPSETTING(0560, "560")
	PORT_DIPSETTING(0564, "564")
	PORT_DIPSETTING(0570, "570")
	PORT_DIPSETTING(0574, "574")
	PORT_DIPSETTING(0600, "600")
	PORT_DIPSETTING(0604, "604")
	PORT_DIPSETTING(0610, "610")
	PORT_DIPSETTING(0614, "614")
	PORT_DIPSETTING(0620, "620")
	PORT_DIPSETTING(0624, "624")
	PORT_DIPSETTING(0630, "630")
	PORT_DIPSETTING(0634, "634")
	PORT_DIPSETTING(0640, "640")
	PORT_DIPSETTING(0644, "644")
	PORT_DIPSETTING(0650, "650")
	PORT_DIPSETTING(0654, "654")
	PORT_DIPSETTING(0660, "660")
	PORT_DIPSETTING(0664, "664")
	PORT_DIPSETTING(0670, "670")
	PORT_DIPSETTING(0674, "674")
	PORT_DIPSETTING(0700, "700")
	PORT_DIPSETTING(0704, "704")
	PORT_DIPSETTING(0710, "710")
	PORT_DIPSETTING(0714, "714")
	PORT_DIPSETTING(0720, "720")
	PORT_DIPSETTING(0724, "724")
	PORT_DIPSETTING(0730, "730")
	PORT_DIPSETTING(0734, "734")
	PORT_DIPSETTING(0740, "740")
	PORT_DIPSETTING(0744, "744")
	PORT_DIPSETTING(0750, "750")
	PORT_DIPSETTING(0754, "754")
	PORT_DIPSETTING(0760, "760")
	PORT_DIPSETTING(0764, "764")
	PORT_DIPSETTING(0770, "770")
	PORT_DIPSETTING(0774, "774")
	PORT_BIT(0176003, IP_ACTIVE_HIGH, IPT_UNUSED) // Other A inputs for 74LS257 multiplexers are grounded

	PORT_START("MODE")
	PORT_DIPNAME(1, 1, "Operating Mode") PORT_DIPLOCATION("J12:1") // Position labeled "EN RX01"
	PORT_DIPSETTING(0, "1 (RX01 Compatible)")
	PORT_DIPSETTING(1, "2 (RX02 Compatible)")

	// Numerous other jumpers exist, but are for debug use only
INPUT_PORTS_END

ioport_constructor dsd4432_device::device_input_ports() const
{
	return INPUT_PORTS_NAME(dsd4432);
}

void dsd4432_device::device_add_mconfig(machine_config &config)
{
	// TODO
}

ROM_START(dsd4432)
	ROM_REGION16_LE(0x400, "bootstrap", 0)
	// Boot PROMs may be up to 512x8 (74S472 or compatible) each, with the high ROM area mapped separately.
	// However, the standard bootstrap program requires only 256 words; pin 16 is ADF on 74S472 but ~E2 on 74S471.
	ROM_LOAD16_BYTE("80035.5a", 0x000, 0x020, CRC(f839c90e) SHA1(aff7a56c228922e45f4bf9f0c838544363239ec2)) // MMI 6309-1J
	ROM_CONTINUE(0x080, 0x020)
	ROM_CONTINUE(0x100, 0x020)
	ROM_CONTINUE(0x180, 0x020)
	ROM_CONTINUE(0x200, 0x020)
	ROM_CONTINUE(0x280, 0x020)
	ROM_CONTINUE(0x300, 0x020)
	ROM_CONTINUE(0x380, 0x020)
	ROM_LOAD16_BYTE("80036.6a", 0x001, 0x020, CRC(9fc1a036) SHA1(5f447bfe90dc06cd195b2dcf7c88ca90c3e82295)) // SN74S471N
	ROM_CONTINUE(0x081, 0x020)
	ROM_CONTINUE(0x101, 0x020)
	ROM_CONTINUE(0x181, 0x020)
	ROM_CONTINUE(0x201, 0x020)
	ROM_CONTINUE(0x281, 0x020)
	ROM_CONTINUE(0x301, 0x020)
	ROM_CONTINUE(0x381, 0x020)

	ROM_REGION(0x200, "hiaddr", 0)
	// A8 = 6B:2, A7 = 6B:1, A6 = 6B:3, A5 = 6B:4, A4 = DIN12, A3 = DIN11, A2 = DIN10, A1 = DIN9, A0 = BS7
	ROM_LOAD("80034.5c", 0x000, 0x200, CRC(a8e89bc9) SHA1(e4b0f519ffbdb413b166301ad3fdc7f43bae1f37)) // MMI 6305-1J

	ROM_REGION(0x200, "loaddr", 0)
	// A8 = 6B:3, A7 = 6B:4, A6 = DIN8, A5 = DIN7, A4 = DIN6, A3 = DIN5, A2 = DIN4, A1 = DIN3, A0 = DIN2
	ROM_LOAD("80033.7c", 0x000, 0x200, CRC(d45c9327) SHA1(de38874bb6038338840fb71c7304a8e462584681)) // MMI 6305-1J

	ROM_REGION(0x400, "shiftmux", 0)
	// A9 = parity, A8 = SR15, A7 = SR11, A6 = SR7, A5 = IF DONE, A4 = ENDMA, A3 = HIGH BYTE L, A2 = 3H:QC, A1 = 3H:QD, A0 = IF DATA
	ROM_LOAD("80032.4h", 0x000, 0x400, CRC(c5c80468) SHA1(12c90cd62d2287ee5018801e4ceb1042051b6783)) // N82S137N

	ROM_REGION(0xf5, "shiftpla", 0)
	ROM_LOAD("80037.7h", 0x00, 0xf5, NO_DUMP) // N82S100N

	ROM_REGION(0xf5, "dmapla", 0)
	ROM_LOAD("80038.9h", 0x00, 0xf5, NO_DUMP) // N82S100N
ROM_END

const tiny_rom_entry *dsd4432_device::device_rom_region() const
{
	return ROM_NAME(dsd4432);
}