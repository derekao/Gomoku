==32716== Memcheck, a memory error detector
==32716== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==32716== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==32716== Command: ./a.out
==32716== 
==32716== Syscall param msg->desc.port.name points to uninitialised byte(s)
==32716==    at 0x1004AB34A: mach_msg_trap (in /usr/lib/system/libsystem_kernel.dylib)
==32716==    by 0x1004AA796: mach_msg (in /usr/lib/system/libsystem_kernel.dylib)
==32716==    by 0x1004A4485: task_set_special_port (in /usr/lib/system/libsystem_kernel.dylib)
==32716==    by 0x10064010E: _os_trace_create_debug_control_port (in /usr/lib/system/libsystem_trace.dylib)
==32716==    by 0x100640458: _libtrace_init (in /usr/lib/system/libsystem_trace.dylib)
==32716==    by 0x1001709DF: libSystem_initializer (in /usr/lib/libSystem.B.dylib)
==32716==    by 0x10002CA1A: ImageLoaderMachO::doModInitFunctions(ImageLoader::LinkContext const&) (in /usr/lib/dyld)
==32716==    by 0x10002CC1D: ImageLoaderMachO::doInitialization(ImageLoader::LinkContext const&) (in /usr/lib/dyld)
==32716==    by 0x1000284A9: ImageLoader::recursiveInitialization(ImageLoader::LinkContext const&, unsigned int, char const*, ImageLoader::InitializerTimingList&, ImageLoader::UninitedUpwards&) (in /usr/lib/dyld)
==32716==    by 0x100028440: ImageLoader::recursiveInitialization(ImageLoader::LinkContext const&, unsigned int, char const*, ImageLoader::InitializerTimingList&, ImageLoader::UninitedUpwards&) (in /usr/lib/dyld)
==32716==    by 0x100027523: ImageLoader::processInitializers(ImageLoader::LinkContext const&, unsigned int, ImageLoader::InitializerTimingList&, ImageLoader::UninitedUpwards&) (in /usr/lib/dyld)
==32716==    by 0x1000275B8: ImageLoader::runInitializers(ImageLoader::LinkContext const&, ImageLoader::InitializerTimingList&) (in /usr/lib/dyld)
==32716==  Address 0x10489fdcc is on thread 1's stack
==32716==  in frame #2, created by task_set_special_port (???:)
==32716==  Uninitialised value was created by a stack allocation
==32716==    at 0x1006400A6: _os_trace_create_debug_control_port (in /usr/lib/system/libsystem_trace.dylib)
==32716== 
==32716== Conditional jump or move depends on uninitialised value(s)
==32716==    at 0x1005F55E8: _platform_memchr$VARIANT$Base (in /usr/lib/system/libsystem_platform.dylib)
==32716==    by 0x1003A14D1: __sfvwrite (in /usr/lib/system/libsystem_c.dylib)
==32716==    by 0x1003A188C: fwrite (in /usr/lib/system/libsystem_c.dylib)
==32716==    by 0x1000D88A1: std::__1::ostreambuf_iterator<char, std::__1::char_traits<char> > std::__1::__pad_and_output<char, std::__1::char_traits<char> >(std::__1::ostreambuf_iterator<char, std::__1::char_traits<char> >, char const*, char const*, char const*, std::__1::ios_base&, char) (in /usr/lib/libc++.1.dylib)
==32716==    by 0x1000D83A6: std::__1::num_put<char, std::__1::ostreambuf_iterator<char, std::__1::char_traits<char> > >::do_put(std::__1::ostreambuf_iterator<char, std::__1::char_traits<char> >, std::__1::ios_base&, char, long) const (in /usr/lib/libc++.1.dylib)
==32716==    by 0x1000CBE5E: std::__1::basic_ostream<char, std::__1::char_traits<char> >::operator<<(int) (in /usr/lib/libc++.1.dylib)
==32716==    by 0x1000013F7: IAPlay (Extern.cpp:26)
==32716==    by 0x10000BFBB: main (main.cpp:38)
==32716==  Uninitialised value was created by a stack allocation
==32716==    at 0x1000D8264: std::__1::num_put<char, std::__1::ostreambuf_iterator<char, std::__1::char_traits<char> > >::do_put(std::__1::ostreambuf_iterator<char, std::__1::char_traits<char> >, std::__1::ios_base&, char, long) const (in /usr/lib/libc++.1.dylib)
==32716== 
==32716== 
==32716== HEAP SUMMARY:
==32716==     in use at exit: 22,800 bytes in 196 blocks
==32716==   total heap usage: 7,852 allocs, 7,656 frees, 718,206 bytes allocated
==32716== 
==32716== LEAK SUMMARY:
==32716==    definitely lost: 544 bytes in 34 blocks
==32716==    indirectly lost: 0 bytes in 0 blocks
==32716==      possibly lost: 72 bytes in 3 blocks
==32716==    still reachable: 4,296 bytes in 7 blocks
==32716==         suppressed: 17,888 bytes in 152 blocks
==32716== Rerun with --leak-check=full to see details of leaked memory
==32716== 
==32716== For counts of detected and suppressed errors, rerun with: -v
==32716== ERROR SUMMARY: 367 errors from 2 contexts (suppressed: 4 from 4)
