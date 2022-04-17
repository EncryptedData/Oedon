using System.Runtime.InteropServices;

namespace Oedon.NativeInterop;
public static class OedonNative
{
    const string OedonNativeLibraryName = "Oedon";

    [DllImport(OedonNativeLibraryName)]
    public static extern int Stub(int a, int b);

    [DllImport(OedonNativeLibraryName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void DoOperations(IntPtr scene, string operations);
}
