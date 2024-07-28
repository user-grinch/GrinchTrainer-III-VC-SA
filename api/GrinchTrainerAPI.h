#pragma once
#define TAPI_VERSION 1.1
typedef void (*T_FUNC)(void* value);

enum TReturnCode {
    TReturn_Success,            // Connection established/ widget init success
    TReturn_VersionMismatch,    // The trainer version is below the required version
    TReturn_ParamError,         // Issues with the parameters passed to the APIs
    TReturn_NoConnection,       // No connection is currently established
    TReturn_CallerFetchError,   // Failed to fetch caller info
    TReturn_Error,              // Unknown error occured ?
};

#ifdef TRAINER_DEV
    #define DLL_WRAPPER __declspec(dllexport)
#else
    #define DLL_WRAPPER __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
    DLL_WRAPPER float TAPI_GetAPIVersion();
    DLL_WRAPPER float TAPI_GetTrainerVersion();

    // Returns true when a successful connection is established. Call rest of the widget apis inside Init()..Close()
    DLL_WRAPPER TReturnCode TAPI_InitConnect(const char* modname, float minVersion);
    DLL_WRAPPER TReturnCode TAPI_CloseConnect();

    // Clears all previosly registered widgets, useful if you're reloading/ unloading your modification
    DLL_WRAPPER TReturnCode TAPI_ClearWidgets();
    
    // Draws space between widgets ImGui::Spacing
    DLL_WRAPPER TReturnCode TAPI_Spacing(float spacing);

    // Draws a simple ImGui::Checkbox widget. Callback is called when widget state changes
    DLL_WRAPPER TReturnCode TAPI_Checkbox(const char* label, bool* v, T_FUNC callback);

    // Draws 1/2/3 ImGui::InputInt/InputFloat/SliderInt/SliderFloat widget. 
    // Callback is called when the value changes
    // InputXXX2 requires DATA_TYPE arr[2]
    // InputXXX3 requires DATA_TYPE arr[3]
    DLL_WRAPPER TReturnCode TAPI_InputInt(const char* label, int* v, T_FUNC callback, int min, int max);
    DLL_WRAPPER TReturnCode TAPI_InputInt2(const char* label, int* v, T_FUNC callback, int min, int max);
    DLL_WRAPPER TReturnCode TAPI_InputInt3(const char* label, int* v, T_FUNC callback, int min, int max);
    DLL_WRAPPER TReturnCode TAPI_InputFloat(const char* label, float* v, T_FUNC callback, float min, float max);
    DLL_WRAPPER TReturnCode TAPI_InputFloat2(const char* label, float* v, T_FUNC callback, float min, float max);
    DLL_WRAPPER TReturnCode TAPI_InputFloat3(const char* label, float* v, T_FUNC callback, float min, float max);
    DLL_WRAPPER TReturnCode TAPI_SliderInt(const char* label, int* v, T_FUNC callback, int min, int max);
    DLL_WRAPPER TReturnCode TAPI_SliderInt2(const char* label, int* v, T_FUNC callback, int min, int max);
    DLL_WRAPPER TReturnCode TAPI_SliderInt3(const char* label, int* v, T_FUNC callback, int min, int max);
    DLL_WRAPPER TReturnCode TAPI_SliderFloat(const char* label, float* v, T_FUNC callback, float min, float max);
    DLL_WRAPPER TReturnCode TAPI_SliderFloat2(const char* label, float* v, T_FUNC callback, float min, float max);
    DLL_WRAPPER TReturnCode TAPI_SliderFloat3(const char* label, float* v, T_FUNC callback, float min, float max);
    DLL_WRAPPER TReturnCode TAPI_InputText(const char* label, char* buf, unsigned int bufsize, T_FUNC callback);

    // Draws ImGui::Combo widget dropdown menu. 
    // items_separated_by_zeros = "Item1\0Item2\0Item3"
    DLL_WRAPPER TReturnCode TAPI_ComboBox(const char* label, int *current_item, const char *items_separated_by_zeros, T_FUNC callback);
#ifdef __cplusplus
}
#endif