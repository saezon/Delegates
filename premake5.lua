workspace "jsolibrary"
   architecture "x86_64"
   configurations { "Debug", "Release" }
   flags {"MultiProcessorCompile"}
   outputdir = "%{cfg.system}-%{cfg.architecture}"

   filter "system:windows"
   systemversion "latest"

   include "jsolibrary"
   group "examples"
      include "examples/01"
   group ""


   
