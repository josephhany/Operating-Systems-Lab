#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x7ba62dba, "module_layout" },
	{ 0x7a00b645, "single_release" },
	{ 0x5671fef2, "seq_read" },
	{ 0x6a85a51d, "seq_lseek" },
	{ 0xc909f65e, "remove_proc_entry" },
	{ 0xdb7305a1, "__stack_chk_fail" },
	{ 0xd4b3235, "pv_cpu_ops" },
	{ 0xe007de41, "kallsyms_lookup_name" },
	{ 0x613f21f5, "proc_create" },
	{ 0xad4c6a80, "seq_printf" },
	{ 0x4811682b, "single_open" },
	{ 0x7c32d0f0, "printk" },
	{ 0x2ea2c95c, "__x86_indirect_thunk_rax" },
	{ 0xbdfb6dbb, "__fentry__" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

