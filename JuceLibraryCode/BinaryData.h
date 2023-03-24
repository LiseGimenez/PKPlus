/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   background_jpg;
    const int            background_jpgSize = 194078;

    extern const char*   buttons_png;
    const int            buttons_pngSize = 609114;

    extern const char*   key_black_sprites_png;
    const int            key_black_sprites_pngSize = 42933;

    extern const char*   key_white_sprites_png;
    const int            key_white_sprites_pngSize = 49820;

    extern const char*   power_button_png;
    const int            power_button_pngSize = 18467;

    extern const char*   CMakeLists_txt;
    const int            CMakeLists_txtSize = 1997;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 6;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
