class Environment {
    public compiletime string("Windows", "MacOS", "Linux", "Unix", "iOS", "Android") os
pre if _WIN32
    os = "Windows"
pre else if _MAC32
    os = "MacOS"
pre else if _LIN32
    os = "Linux"
pre else if _NIX32
    os = "Unix"
pre else if _IOS32
    os = "iOS"
pre else if _AND32
    os = "Android"
pre end

    public container Architecture {
        bool is64Bit
        bool is32Bit: !is64Bit

        string archName
        string toString(): archName
    }

    compiletime Architecture arch
pre if _64BITS
    arch.is64Bit = true
pre else
    arch.is64Bit = false
pre end

pre if _x86
    arch.archName = "x86"
pre else if _x86_64
    arch.archName = "x86_64"
pre else if _ARM32
    arch.archName = "arm32"
pre else if _ARM64
    arch.archName = "arm64"
pre end
}