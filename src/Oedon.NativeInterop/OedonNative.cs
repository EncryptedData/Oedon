using System.Runtime.InteropServices;

namespace Oedon.NativeInterop;
public static class OedonNative
{
    const string OedonNativeLibraryName = "Oedon";

    [DllImport(OedonNativeLibraryName)]
    public static extern int Stub(int a, int b);
}
