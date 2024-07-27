#pragma once
#define TAPI_VERSION 1.0
typedef void (*T_FUNC)(void* value);

#ifdef TRAINER_DEV
    #define DLL_WRAPPER __declspec(dllexport)
#else
    #define DLL_WRAPPER __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
    float TAPI_GetTrainerVersion();

    // Widgets
    // Draws a simple ImGui::Checkbox widget. Callback is called when widget state changes
    DLL_WRAPPER void TAPI_RegisterCheckbox(const char* label, const char* modname, bool* v, T_FUNC callback);
    
    // Draws 1/2/3 ImGui::InputInt/InputFloat/SliderInt/SliderFloat widget. 
    // Callback is called when the value changes
    // InputXXX2 requires DATA_TYPE arr[2]
    // InputXXX3 requires DATA_TYPE arr[3]
    DLL_WRAPPER void TAPI_RegisterInputInt(const char* label, const char* modname, int* v, T_FUNC callback, int min, int max);
    DLL_WRAPPER void TAPI_RegisterInputInt2(const char* label, const char* modname, int* v, T_FUNC callback, int min, int max);
    DLL_WRAPPER void TAPI_RegisterInputInt3(const char* label, const char* modname, int* v, T_FUNC callback, int min, int max);
    DLL_WRAPPER void TAPI_RegisterInputFloat(const char* label, const char* modname, float* v, T_FUNC callback, float min, float max);
    DLL_WRAPPER void TAPI_RegisterInputFloat2(const char* label, const char* modname, float* v, T_FUNC callback, float min, float max);
    DLL_WRAPPER void TAPI_RegisterInputFloat3(const char* label, const char* modname, float* v, T_FUNC callback, float min, float max);
    DLL_WRAPPER void TAPI_RegisterSliderInt(const char* label, const char* modname, int* v, T_FUNC callback, int min, int max);
    DLL_WRAPPER void TAPI_RegisterSliderInt2(const char* label, const char* modname, int* v, T_FUNC callback, int min, int max);
    DLL_WRAPPER void TAPI_RegisterSliderInt3(const char* label, const char* modname, int* v, T_FUNC callback, int min, int max);
    DLL_WRAPPER void TAPI_RegisterSliderFloat(const char* label, const char* modname, float* v, T_FUNC callback, float min, float max);
    DLL_WRAPPER void TAPI_RegisterSliderFloat2(const char* label, const char* modname, float* v, T_FUNC callback, float min, float max);
    DLL_WRAPPER void TAPI_RegisterSliderFloat3(const char* label, const char* modname, float* v, T_FUNC callback, float min, float max);
    DLL_WRAPPER void TAPI_RegisterInputString(const char* label, const char* modname, char* buf, unsigned int buf_size, T_FUNC callback, float min, float max);

    // Draws ImGui::Combo widget dropdown menu. 
    // items_separated_by_zeros = "Item1\0Item2\0Item3"
    DLL_WRAPPER void TAPI_RegisterComboBox(const char* label, const char* modname, int *current_item, const char *items_separated_by_zeros, T_FUNC callback);
#ifdef __cplusplus
}
#endif