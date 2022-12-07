/*******************************************************************************
@file     startup.h
@author   Rajmund Szymanski
@date     01.03.2021
@brief    Startup file header for gcc compiler.
*******************************************************************************/

#include <string.h>

#pragma once

/*******************************************************************************
 Additional definitions
*******************************************************************************/

#define __ALIAS(function) __attribute__ ((weak, alias(#function)))
#define __VECTORS         __attribute__ ((used, section(".vectors")))
#define __CAST(sp)        (void(*)(void))(intptr_t)(sp)

/*******************************************************************************
 Prototypes of external functions
*******************************************************************************/

__WEAK __USED void hardware_init_hook        ( void );
__WEAK __USED void software_init_hook        ( void );
__WEAK __USED void initialise_monitor_handles( void );
__WEAK __USED void __libc_init_array         ( void );
__WEAK __USED void __libc_fini_array         ( void );
  __NO_RETURN void _exit                     (  int );
               int main                      ( void );

/*******************************************************************************
 Symbols defined in linker script
*******************************************************************************/

extern char _estack[];
extern char _sdata[];
extern char _edata[];
extern char _sidata[];
extern char _sbss[];
extern char _ebss[];

/*******************************************************************************
 Default reset procedures
*******************************************************************************/

__STATIC_INLINE __NO_RETURN
void __main( void )
{
	int result;
	/* Early hardware init hook */
	hardware_init_hook();
	/* Initialize the data segment */
	memcpy(_sdata, _sidata, (size_t)(_edata - _sdata));
	/* Zero fill the bss segment */
	memset(_sbss, 0, (size_t)(_ebss - _sbss));
	/* Early software init hook */
	software_init_hook();
	/* Call global & static constructors */
	__libc_init_array();
	/* Initialize monitor handles */
	initialise_monitor_handles();
	/* Call the application's entry point */
	result = main();
	/* Call global & static destructors */
	__libc_fini_array();
	/* Go into an infinite loop */
	_exit(result);
}

/******************************************************************************/
