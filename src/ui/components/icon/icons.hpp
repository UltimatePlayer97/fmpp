#pragma once

#include <string_view>
#include <filesystem>
#include <algorithm>
#include <cctype>

using namespace std;

// REQUIRES NERD FONT BE INSTALLED ON THE IDE AND TERMINAL EMULATOR
namespace Icons {
    // general / misc
    constexpr string_view FOLDER = "󰉋";
    constexpr string_view FOLDER_OPEN = "󰝰";
    constexpr string_view ARCHIVE = "󰛫";
    constexpr string_view IMAGE = "󰋩";
    constexpr string_view DEFAULT = "󰈔";
    constexpr string_view PDF = "󰈦";
    constexpr string_view AUDIO = "󰎈";
    constexpr string_view VIDEO = "󰕼";
    constexpr string_view FONT = "󰛖";
    constexpr string_view DOCUMENT = "󰈙";
    constexpr string_view SPREADSHEET = "󰈛";
    constexpr string_view PRESENTATION = "󰈧";
    constexpr string_view DATABASE = "󰆼";
    constexpr string_view LOCK = "󰌾";
    constexpr string_view CERT = "󰄤";
    constexpr string_view KEY = "󰌋";
    constexpr string_view LOG = "󰌱";
    constexpr string_view CONFIG = "";
    constexpr string_view BINARY = "";
    constexpr string_view ISO = "󰗮";
    constexpr string_view TORRENT = "󰙦";
    constexpr string_view EMAIL = "󰇮";
    constexpr string_view CALENDAR = "󰃭";
    constexpr string_view EBOOK = "󰂺";
    constexpr string_view SUBTITLE = "󰨖";
    constexpr string_view THREE_D = "󰆧";

    // platform / executable
    constexpr string_view WINDOWS_EXE = "󰖳"; // .exe / .msi / .bat / .cmd
    constexpr string_view APPLE = "󰀵"; // .app / .dmg / .pkg

    // distro specific
    constexpr string_view LINUX = "󰌽";
    constexpr string_view DEBIAN   = "󰣚";
    constexpr string_view FEDORA   = "󰣛";
    constexpr string_view UBUNTU   = "󰕈";
    constexpr string_view FLATPAK  = "";
    constexpr string_view APPIMAGE = "󰵆";

    // programming languages
    constexpr string_view PYTHON = "󰌠";
    constexpr string_view CPP = "󰙲";
    constexpr string_view CSHARP = "󰌛";
    constexpr string_view C = "󰙱";
    constexpr string_view JAVASCRIPT = "󰌞";
    constexpr string_view TYPESCRIPT = "󰛦";
    constexpr string_view JAVA = "󰬷";
    constexpr string_view KOTLIN = "󱈙";
    constexpr string_view GO = "󰟓";
    constexpr string_view RUST = "󱘗";
    constexpr string_view RUBY = "󰴭";
    constexpr string_view PHP = "󰌟";
    constexpr string_view SWIFT = "󰛥";
    constexpr string_view SCALA = "";
    constexpr string_view LUA = "󰢱";
    constexpr string_view HASKELL = "󰲒";
    constexpr string_view ELIXIR = "";
    constexpr string_view ERLANG = "";
    constexpr string_view CLOJURE = "";
    constexpr string_view FSHARP = "";
    constexpr string_view VB = "󰛤"; // .vb / .vbs
    constexpr string_view PERL = "";
    constexpr string_view R_LANG = "󰟔";
    constexpr string_view DART = "";
    constexpr string_view ZIG = "";
    constexpr string_view NIM = "";
    constexpr string_view CRYSTAL = "";
    constexpr string_view OCAML = "";
    constexpr string_view JULIA = "";
    constexpr string_view GROOVY = "";
    constexpr string_view ASSEMBLY = "";

    // web / markup / style
    constexpr string_view HTML = "󰌝";
    constexpr string_view CSS = "󰌜";
    constexpr string_view SCSS = "󰌜";
    constexpr string_view LESS = "";
    constexpr string_view XML = "󰗀";
    constexpr string_view SVG = "󰜡";
    constexpr string_view JSX = "󰜈";
    constexpr string_view VUE = "󰡄";
    constexpr string_view SVELTE = "";
    constexpr string_view WASM = "";

    // data / config / serialization
    constexpr string_view JSON = "󰘦";
    constexpr string_view YAML = "";
    constexpr string_view TOML = "";
    constexpr string_view INI = "";
    constexpr string_view CSV = "󰈙";
    constexpr string_view SQL = "";
    constexpr string_view GRAPHQL = "󰡷";
    constexpr string_view PROTO = "󰈲";

    // shell / scripting
    constexpr string_view SHELL = ""; // .sh / .bash / .zsh / .fish
    constexpr string_view POWERSHELL = "󰨊";
    constexpr string_view MAKEFILE = "";

    // devops / infra
    constexpr string_view DOCKER = "󰡨";
    constexpr string_view TERRAFORM = "󱁢";
    constexpr string_view ANSIBLE = "󱂚";
    constexpr string_view KUBERNETES = "󱃾";
    constexpr string_view NGINX = "";

    // version control / ci
    constexpr string_view GIT = "󰊢";
    constexpr string_view GITIGNORE = "󰊢";

    // text / docs
    constexpr string_view MARKDOWN = "󰍔";
    constexpr string_view RST = "󰊄";
    constexpr string_view LATEX = "";
    constexpr string_view ORG = "󰅇";
    constexpr string_view TXT = "󰈙";

    // runtime / build artifacts
    constexpr string_view OBJECT_FILE = "󰗚"; // .o / .obj
    constexpr string_view LIB = "󰗛"; // .a / .lib / .so / .dll / .dylib
    constexpr string_view ELF = ""; // linux binaries (no ext or .elf)
}

inline string_view get_icon_for_item(const filesystem::path& path, bool is_directory) {
    if (is_directory) {
        return Icons::FOLDER;
    }

    string ext = path.extension().string();
    transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) {
        return tolower(c);
    });

    // special filenames (no extension)
    {
        string filename = path.filename().string();
        transform(filename.begin(), filename.end(), filename.begin(), [](unsigned char c) {
            return tolower(c);
        });
        if (filename == "makefile" || filename == "gnumakefile") return Icons::MAKEFILE;
        if (filename == "dockerfile") return Icons::DOCKER;
        if (filename == "gemfile" || filename == "rakefile") return Icons::RUBY;
        if (filename == "jenkinsfile") return Icons::LINUX;
        if (filename == ".gitignore" || filename == ".gitattributes" ||
            filename == ".gitmodules") return Icons::GITIGNORE;
        if (filename == ".env" || filename == ".envrc") return Icons::CONFIG;
        if (filename == "vagrantfile") return Icons::LINUX;
        if (filename == "procfile") return Icons::LINUX;
    }

    // images
    if (ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".gif" ||
        ext == ".bmp" || ext == ".tiff" || ext == ".tif" || ext == ".webp" ||
        ext == ".ico" || ext == ".heic" || ext == ".heif" || ext == ".avif" ||
        ext == ".raw" || ext == ".cr2" || ext == ".nef" || ext == ".arw" ||
        ext == ".psd" || ext == ".xcf" || ext == ".kra" || ext == ".ora")
        return Icons::IMAGE;

    if (ext == ".svg" || ext == ".svgz") return Icons::SVG;

    // video
    if (ext == ".mp4" || ext == ".mkv" || ext == ".avi" || ext == ".mov" ||
        ext == ".wmv" || ext == ".flv" || ext == ".webm" || ext == ".m4v" ||
        ext == ".mpg" || ext == ".mpeg" || ext == ".3gp" || ext == ".ogv" ||
        ext == ".ts" || ext == ".mts" || ext == ".m2ts" || ext == ".vob" ||
        ext == ".rmvb" || ext == ".divx")
        return Icons::VIDEO;

    // audio
    if (ext == ".mp3" || ext == ".wav" || ext == ".flac" || ext == ".aac" ||
        ext == ".ogg" || ext == ".opus" || ext == ".m4a" || ext == ".wma" ||
        ext == ".aiff" || ext == ".alac" || ext == ".mid" || ext == ".midi" ||
        ext == ".mka" || ext == ".ape" || ext == ".wv")
        return Icons::AUDIO;

    // archives
    if (ext == ".zip" || ext == ".tar" || ext == ".gz" || ext == ".bz2" ||
        ext == ".xz" || ext == ".lzma" || ext == ".zst" || ext == ".7z" ||
        ext == ".rar" || ext == ".cab" || ext == ".lz4" || ext == ".lz" ||
        ext == ".tgz" || ext == ".tbz2" || ext == ".txz" || ext == ".tlzma" ||
        ext == ".tzst" || ext == ".br" || ext == ".ace" || ext == ".arj" ||
        ext == ".lzh" || ext == ".z" || ext == ".zz")
        return Icons::ARCHIVE;

    // documents
    if (ext == ".pdf") return Icons::PDF;
    if (ext == ".doc" || ext == ".docx" || ext == ".odt" ||
        ext == ".rtf" || ext == ".pages") return Icons::DOCUMENT;
    if (ext == ".xls" || ext == ".xlsx" || ext == ".ods" ||
        ext == ".numbers") return Icons::SPREADSHEET;
    if (ext == ".ppt" || ext == ".pptx" || ext == ".odp" ||
        ext == ".key") return Icons::PRESENTATION;
    if (ext == ".epub" || ext == ".mobi" || ext == ".azw" ||
        ext == ".azw3" || ext == ".fb2" || ext == ".lit") return Icons::EBOOK;
    if (ext == ".txt" || ext == ".text" || ext == ".asc") return Icons::TXT;
    if (ext == ".md" || ext == ".mdx" || ext == ".markdown") return Icons::MARKDOWN;
    if (ext == ".rst") return Icons::RST;
    if (ext == ".tex" || ext == ".ltx" || ext == ".sty" ||
        ext == ".cls" || ext == ".bib") return Icons::LATEX;
    if (ext == ".org") return Icons::ORG;

    // fonts ───────────────────────────────────────────────────────────────────
    if (ext == ".ttf" || ext == ".otf" || ext == ".woff" ||
        ext == ".woff2"|| ext == ".eot" || ext == ".pfb" ||
        ext == ".pfm" || ext == ".fon")
        return Icons::FONT;

    // subtitles
    if (ext == ".srt" || ext == ".ass" || ext == ".ssa" ||
        ext == ".vtt" || ext == ".sub" || ext == ".sbv")
        return Icons::SUBTITLE;

    // 3d models
    if (ext == ".obj" || ext == ".fbx" || ext == ".gltf" || ext == ".glb" ||
        ext == ".stl" || ext == ".dae" || ext == ".blend"|| ext == ".3ds" ||
        ext == ".ply" || ext == ".usd" || ext == ".usda" || ext == ".usdc")
        return Icons::THREE_D;

    // disk images / iso
    if (ext == ".iso" || ext == ".img" || ext == ".vhd" ||
        ext == ".vhdx" || ext == ".vmdk" || ext == ".qcow2"|| ext == ".vdi" ||
        ext == ".nrg" || ext == ".mdf" || ext == ".bin" || ext == ".cue")
        return Icons::ISO;

    // email / calendar
    if (ext == ".eml" || ext == ".msg" || ext == ".mbox" || ext == ".pst" ||
        ext == ".ost" || ext == ".emlx")
        return Icons::EMAIL;
    if (ext == ".ics" || ext == ".vcf" || ext == ".vcard")
        return Icons::CALENDAR;

    // torrent
    if (ext == ".torrent") return Icons::TORRENT;

    // crypto / security
    if (ext == ".pem" || ext == ".crt" || ext == ".cer" || ext == ".der" ||
        ext == ".ca" || ext == ".p12" || ext == ".pfx" || ext == ".csr" ||
        ext == ".p7b" || ext == ".p7c")
        return Icons::CERT;
    if (ext == ".gpg" || ext == ".pgp" || ext == ".asc" || ext == ".sig")
        return Icons::LOCK;
    if (ext == ".pub" || ext == ".ppk" || ext == ".key")
        return Icons::KEY;

    // logs
    if (ext == ".log" || ext == ".logs")
        return Icons::LOG;

    // database
    if (ext == ".sql" || ext == ".sqlite" || ext == ".sqlite3" || ext == ".db" ||
        ext == ".db3" || ext == ".mdb" || ext == ".accdb" || ext == ".dbf")
        return Icons::DATABASE;

    // data / serialization
    if (ext == ".json" || ext == ".jsonc" || ext == ".json5") return Icons::JSON;
    if (ext == ".yaml" || ext == ".yml") return Icons::YAML;
    if (ext == ".toml") return Icons::TOML;
    if (ext == ".ini" || ext == ".cfg" || ext == ".conf" ||
        ext == ".config") return Icons::CONFIG;
    if (ext == ".xml" || ext == ".xsd" || ext == ".xsl" ||
        ext == ".xslt" || ext == ".plist"|| ext == ".wsdl" ||
        ext == ".rss" || ext == ".atom" || ext == ".nfo") return Icons::XML;
    if (ext == ".csv" || ext == ".tsv" || ext == ".psv") return Icons::CSV;
    if (ext == ".proto") return Icons::PROTO;
    if (ext == ".graphql" || ext == ".gql") return Icons::GRAPHQL;

    // web / markup
    if (ext == ".html" || ext == ".htm" || ext == ".xhtml" ||
        ext == ".jinja"|| ext == ".jinja2"|| ext == ".j2" ||
        ext == ".hbs" || ext == ".ejs" || ext == ".pug" ||
        ext == ".twig" || ext == ".liquid"|| ext == ".erb")
        return Icons::HTML;
    if (ext == ".css") return Icons::CSS;
    if (ext == ".scss" || ext == ".sass") return Icons::SCSS;
    if (ext == ".less") return Icons::LESS;
    if (ext == ".wasm") return Icons::WASM;

    // shell / scripting
    if (ext == ".sh" || ext == ".bash" || ext == ".zsh" || ext == ".fish" ||
        ext == ".ksh" || ext == ".csh" || ext == ".tcsh" || ext == ".dash" ||
        ext == ".profile"|| ext == ".bashrc"|| ext == ".zshrc")
        return Icons::SHELL;
    if (ext == ".ps1" || ext == ".psm1" || ext == ".psd1" || ext == ".ps1xml")
        return Icons::POWERSHELL;
    if (ext == ".bat" || ext == ".cmd") return Icons::WINDOWS_EXE;
    if (ext == ".mk" || ext == ".mak" || ext == ".make") return Icons::MAKEFILE;

    // programming languages
    if (ext == ".py" || ext == ".pyw" || ext == ".pyi" ||
        ext == ".pyc" || ext == ".pyd" || ext == ".pyo") return Icons::PYTHON;

    if (ext == ".js" || ext == ".mjs" || ext == ".cjs") return Icons::JAVASCRIPT;
    if (ext == ".jsx") return Icons::JSX;
    if (ext == ".ts") return Icons::TYPESCRIPT;
    if (ext == ".tsx") return Icons::JSX; // close enough
    if (ext == ".vue") return Icons::VUE;
    if (ext == ".svelte") return Icons::SVELTE;

    if (ext == ".cpp" || ext == ".cxx" || ext == ".cc" ||
        ext == ".c++" || ext == ".hpp" || ext == ".hxx" ||
        ext == ".hh" || ext == ".h++" || ext == ".ipp" ||
        ext == ".tpp" || ext == ".inl") return Icons::CPP;
    if (ext == ".c" || ext == ".h") return Icons::C;

    if (ext == ".cs" || ext == ".csx" || ext == ".cake") return Icons::CSHARP;
    if (ext == ".vb" || ext == ".vbs" || ext == ".bas") return Icons::VB;
    if (ext == ".fs" || ext == ".fsi" || ext == ".fsx" ||
        ext == ".fsscript") return Icons::FSHARP;

    if (ext == ".java" || ext == ".class"|| ext == ".jar" ||
        ext == ".war" || ext == ".ear") return Icons::JAVA;
    if (ext == ".kt" || ext == ".kts") return Icons::KOTLIN;
    if (ext == ".scala"|| ext == ".sc") return Icons::SCALA;
    if (ext == ".groovy"|| ext == ".gvy" || ext == ".gy" ||
        ext == ".gsh") return Icons::GROOVY;
    if (ext == ".clj" || ext == ".cljs" || ext == ".cljc" ||
        ext == ".edn") return Icons::CLOJURE;

    if (ext == ".go") return Icons::GO;
    if (ext == ".rs") return Icons::RUST;
    if (ext == ".rb" || ext == ".rake" || ext == ".gemspec" ||
        ext == ".rbs" || ext == ".ru") return Icons::RUBY;
    if (ext == ".php" || ext == ".phtml"|| ext == ".php3" ||
        ext == ".php4" || ext == ".php5" || ext == ".php7" ||
        ext == ".php8" || ext == ".phps") return Icons::PHP;
    if (ext == ".swift") return Icons::SWIFT;
    if (ext == ".lua" || ext == ".luac") return Icons::LUA;
    if (ext == ".pl" || ext == ".pm" || ext == ".t" ||
        ext == ".pod") return Icons::PERL;
    if (ext == ".r" || ext == ".rmd" || ext == ".rnw") return Icons::R_LANG;
    if (ext == ".dart") return Icons::DART;
    if (ext == ".zig" || ext == ".zon") return Icons::ZIG;
    if (ext == ".nim" || ext == ".nims" || ext == ".nimble") return Icons::NIM;
    if (ext == ".cr") return Icons::CRYSTAL;
    if (ext == ".ml" || ext == ".mli" || ext == ".re" ||
        ext == ".rei") return Icons::OCAML;
    if (ext == ".ex" || ext == ".exs" || ext == ".eex" ||
        ext == ".leex" || ext == ".heex") return Icons::ELIXIR;
    if (ext == ".erl" || ext == ".hrl") return Icons::ERLANG;
    if (ext == ".hs" || ext == ".lhs" || ext == ".cabal") return Icons::HASKELL;
    if (ext == ".jl") return Icons::JULIA;

    if (ext == ".s" || ext == ".asm" || ext == ".nasm" ||
        ext == ".masm" || ext == ".inc") return Icons::ASSEMBLY;

    // devops / infra
    if (ext == ".dockerfile" || path.filename().string() == "Dockerfile") return Icons::DOCKER;
    if (ext == ".tf" || ext == ".tfvars" || ext == ".tfstate" || ext == ".hcl") return Icons::TERRAFORM;

    // git
    if (ext == ".patch"|| ext == ".diff") return Icons::GIT;

    // platform executables / installers
    if (ext == ".exe" || ext == ".msi" || ext == ".msix" ||
        ext == ".appx" || ext == ".appxbundle") return Icons::WINDOWS_EXE;
    if (ext == ".app" || ext == ".ipa" || ext == ".pkg" ||
        ext == ".dmg" || ext == ".mpkg" || ext == ".xip") return Icons::APPLE;

    // distro specific
    if (ext == ".deb") return Icons::DEBIAN;
    if (ext == ".rpm") return Icons::FEDORA;
    if (ext == ".snap") return Icons::UBUNTU;
    if (ext == ".flatpak") return Icons::FLATPAK;
    if (ext == ".appimage") return Icons::APPIMAGE;

    // build artifacts / native libs
    if (ext == ".o" || ext == ".obj") return Icons::OBJECT_FILE;
    if (ext == ".a" || ext == ".lib" || ext == ".so" ||
        ext == ".dll" || ext == ".dylib"|| ext == ".pyd") return Icons::LIB;

    return Icons::DEFAULT;
}
