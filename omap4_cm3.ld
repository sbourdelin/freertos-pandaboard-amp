ENTRY(ResetISR)

MEMORY
{
    TEXT (rwx) : ORIGIN = 0x00000000, LENGTH = 1M
    DATA (rwx) : ORIGIN = 0x80000000, LENGTH = 1M
    TRACE (rwx) : ORIGIN = 0x90000000, LENGTH = 1M
}

SECTIONS
{
    .text : 
    { 
	_text = .;
	KEEP(*(.isr_vector));
	. = ALIGN(1024);
	* (.text*);
	* (.rodata*);
	* (.init*);
	* (.fini*);
	_etext = .;
    } > TEXT

    .data :
    {
	_data = .;
	* (vdata);
	* (.data);
	_edata = .;
    } > DATA

    .bss :
    {
	. = ALIGN(4);
	_bss = .;
	* (.bss);
	* (COMMON);
	_ebss = .;
    } > DATA
    
    .resource_size :
    {
	KEEP(*(.resource_size));
    } > DATA

    .resource_table :
    {
	KEEP(*(.resource_table));
    } > DATA
}
