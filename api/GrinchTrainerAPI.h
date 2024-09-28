/*
 * API provided for GrinchTrainer v1.0 Release
 *
 * 
 * Usage:
 * - Initialize a connection with TAPI_InitConnect(). This step is required to establish a link between your mod and the trainer.
 * - Add various widgets such as buttons, sliders, and text using the provided functions (e.g., TAPI_Button, TAPI_SliderInt).
 * - If you need to clear the interface or reload widgets dynamically, use TAPI_ClearWidgets(). This is helpful when your mod needs to refresh or reinitialize the UI.
 * - Close the connection with TAPI_CloseConnect() after you are done. This ensures that resources are properly released and the connection is terminated.
*/

#pragma once
#define TAPI_VERSION 16000  

typedef void (*T_FUNC)(void* value); 

enum TReturnCode {
    TReturn_Success,            // Connection established or widget initialized successfully
    TReturn_VersionMismatch,    // The trainer version is below the required version for compatibility
    TReturn_ParamError,         // There was an error in the parameters passed to one of the API functions
    TReturn_NoConnection,       // No active connection is established
    TReturn_CallerFetchError,   // Failed to retrieve caller information
    TReturn_Error,              // An unknown error occurred
};

#ifdef TRAINER_DEV
    #define T_WRAPPER __declspec(dllexport) 
#else
    #define T_WRAPPER __declspec(dllimport)    
#endif

#ifdef __cplusplus
extern "C" {
#endif

    // Functions to get API and Trainer version
    T_WRAPPER int TAPI_GetAPIVersion();
    T_WRAPPER int TAPI_GetTrainerVersion();

    /*
     * TAPI_InitConnect
     * 
     * Initializes a connection to the trainer. 
     * The rest of the widget-related API functions should be called only after a successful connection.
     * 
     * @param modname: Name of the mod connecting to the trainer.
     * @param minVersion: Minimum required version of the trainer for compatibility.
     * @return TReturnCode: Result of the connection initialization.
     */
    T_WRAPPER TReturnCode TAPI_InitConnect(const char* modname, int minVersion);

    /*
     * TAPI_CloseConnect
     *
     * Closes the connection to the trainer.
     * It should be called to clean up and release resources once your work with the trainer is complete.
     */
    T_WRAPPER TReturnCode TAPI_CloseConnect();

    /*
     * TAPI_ClearWidgets
     *
     * Clears all previously registered widgets. This is useful for resetting or reloading the UI.
     * You might use this if the interface needs to update frequently, such as every frame.
     */
    T_WRAPPER TReturnCode TAPI_ClearWidgets();

    /*
     * Widget-related API functions for UI construction
     */

    // Adds space between widgets, similar to ImGui::Spacing. The values x and y define how much spacing is added.
    T_WRAPPER TReturnCode TAPI_Spacing(float x, float y);

    // Adds a widget on the same horizontal line as the previous one (ImGui::SameLine).
    T_WRAPPER TReturnCode TAPI_SameLine();

    // Columns-related functions for multi-column layouts. TAPI_Columns creates 'count' columns, and TAPI_NextColumn moves to the next column.
    T_WRAPPER TReturnCode TAPI_Columns(size_t count);
    T_WRAPPER TReturnCode TAPI_NextColumn();

    // Button-related functions: TAPI_Button creates a button with the given label and callback.
    // Button2 and Button3 create two or three horizontally stacked buttons respectively.
    T_WRAPPER TReturnCode TAPI_Button(const char* label, T_FUNC callback);

    // Checkbox widget: Creates a checkbox with a label, and calls the callback when its state changes.
    // Checkbox2 creates two horizontally stacked checkboxes.
    T_WRAPPER TReturnCode TAPI_Checkbox(const char* label, bool* v, T_FUNC callback);

    /*
     * Input and Slider widgets for integers and floats
     * 
     * - TAPI_InputXXX: Creates input fields for integers and floats. These widgets accept a callback function when the value changes.
     * - The suffix 2 and 3 denotes that the widget will handle arrays of size 2 or 3 respectively.
     */
    T_WRAPPER TReturnCode TAPI_InputInt(const char* label, int* v, T_FUNC callback, int min, int max);
    T_WRAPPER TReturnCode TAPI_InputInt2(const char* label, int* v, T_FUNC callback, int min, int max);
    T_WRAPPER TReturnCode TAPI_InputInt3(const char* label, int* v, T_FUNC callback, int min, int max);
    T_WRAPPER TReturnCode TAPI_InputFloat(const char* label, float* v, T_FUNC callback, float min, float max);
    T_WRAPPER TReturnCode TAPI_InputFloat2(const char* label, float* v, T_FUNC callback, float min, float max);
    T_WRAPPER TReturnCode TAPI_InputFloat3(const char* label, float* v, T_FUNC callback, float min, float max);

    // Slider widgets for integer and float values, with suffixes 2 and 3 indicating multi-element arrays.
    T_WRAPPER TReturnCode TAPI_SliderInt(const char* label, int* v, T_FUNC callback, int min, int max);
    T_WRAPPER TReturnCode TAPI_SliderInt2(const char* label, int* v, T_FUNC callback, int min, int max);
    T_WRAPPER TReturnCode TAPI_SliderInt3(const char* label, int* v, T_FUNC callback, int min, int max);
    T_WRAPPER TReturnCode TAPI_SliderFloat(const char* label, float* v, T_FUNC callback, float min, float max);
    T_WRAPPER TReturnCode TAPI_SliderFloat2(const char* label, float* v, T_FUNC callback, float min, float max);
    T_WRAPPER TReturnCode TAPI_SliderFloat3(const char* label, float* v, T_FUNC callback, float min, float max);

    // InputText: Creates a text input box. Callback is triggered when text is modified.
    T_WRAPPER TReturnCode TAPI_InputText(const char* label, char* buf, unsigned int bufsize, T_FUNC callback);

    /*
     * Combo box widget for dropdown selection.
     * The items should be separated by null terminators ('\0').
     * For example: "Item1\0Item2\0Item3"
     */
    T_WRAPPER TReturnCode TAPI_ComboBox(const char* label, int *current_item, const char *items_separated_by_zeros, T_FUNC callback);

    /*
     * Color picker widgets
     * These allow picking RGB and RGBA colors, either as unsigned char (0-255) or float (0.0-1.0) values.
     */
    T_WRAPPER TReturnCode TAPI_ColorPicker3(const char* label, unsigned char* r, unsigned char* g, unsigned char* b, T_FUNC callback);
    T_WRAPPER TReturnCode TAPI_ColorPicker4(const char* label, unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a, T_FUNC callback);
    T_WRAPPER TReturnCode TAPI_ColorPicker3F(const char* label, float* r, float* g, float* b, T_FUNC callback);
    T_WRAPPER TReturnCode TAPI_ColorPicker4F(const char* label, float* r, float* g, float* b, float* a, T_FUNC callback);

    /*
     * Text widget: Draws simple text on the UI.
     */
    T_WRAPPER TReturnCode TAPI_Text(const char* label);

#ifdef __cplusplus
}
#endif