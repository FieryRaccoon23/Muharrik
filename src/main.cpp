#define SDL_MAIN_HANDLED 1
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <cstdio>
//#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>

// void VulkanCheck()
// {
//     // Print loader-supported Vulkan version (optional)
//     uint32_t apiVersion = VK_API_VERSION_1_0;
//     vkEnumerateInstanceVersion(&apiVersion);
//     std::cout << "Vulkan API version: "
//               << VK_VERSION_MAJOR(apiVersion) << "."
//               << VK_VERSION_MINOR(apiVersion) << "."
//               << VK_VERSION_PATCH(apiVersion) << "\n";

//     // App info (optional, but nice)
//     VkApplicationInfo appInfo{};
//     appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
//     appInfo.pApplicationName = "HelloVulkan";
//     appInfo.apiVersion = VK_API_VERSION_1_0;

//     // IMPORTANT on macOS/MoltenVK:
//     // opt-in to enumerate portability drivers (MoltenVK)
//     const char* exts[] = { VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME };

//     VkInstanceCreateInfo ci{};
//     ci.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
//     ci.pApplicationInfo = &appInfo;
//     ci.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
//     ci.enabledExtensionCount = 1;
//     ci.ppEnabledExtensionNames = exts;

//     VkInstance instance = VK_NULL_HANDLE;
//     VkResult r = vkCreateInstance(&ci, nullptr, &instance);
//     if (r != VK_SUCCESS) {
//         std::cerr << "vkCreateInstance failed: " << r << "\n";
//     }

//     uint32_t count = 0;
//     r = vkEnumeratePhysicalDevices(instance, &count, nullptr);
//     std::cout << "Physical devices found: " << count << "\n";

//     vkDestroyInstance(instance, nullptr);
// }

int main(int argc, char** argv)
{
    (void)argc; (void)argv;

    SDL_SetMainReady();  // important when using SDL_MAIN_HANDLED

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL3 Test", 800, 600, 0);
    if (!window) {
        std::printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;
        }
        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    glm::vec2 v(1.0f, 2.0f);
    std::printf("%f %f\n", v.x, v.y);

    //VulkanCheck();

    return 0;
}
