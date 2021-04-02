project "01"
   kind "ConsoleApp"
   language "c++"
   cppdialect "C++17"
   targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
   objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
   debugdir ("%{wks.location}/bin/"  .. outputdir .. "/%{prj.name}")

   files { "src/**.h","src/**.cpp"}
   vpaths{
      ["include"] = "**.h",
      ["src"] = "**.cpp"
   }
   defines {}
   includedirs {"src","%{wks.location}/jso_delegates/src"}

   links{"jso_delegates"}



   filter "configurations:Debug"
    defines { "_DEBUG" }
    symbols "On"
    runtime "Debug"
    targetname "%{prj.name}_d"


   filter "configurations:Release"
    optimize "On"
    runtime "Release"
