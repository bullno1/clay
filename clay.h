#pragma once
// VERSION: 0.11

/*
    NOTE: In order to use this library you must define
    the following macro in exactly one file, _before_ including clay.h:

    #define CLAY_IMPLEMENTATION
    #include "clay.h"

    See the examples folder for details.
*/

#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"

// -----------------------------------------
// HEADER DECLARATIONS ---------------------
// -----------------------------------------

#ifndef CLAY_HEADER
#define CLAY_HEADER

#ifdef CLAY_WASM
#define CLAY_WASM_EXPORT(name) __attribute__((export_name(name)))
#else
#define CLAY_WASM_EXPORT(null)
#endif

// Public Macro API ------------------------

#ifdef __cplusplus
#define CLAY__CONFIG_WRAPPER(type, ...) __VA_ARGS__
#else
#define CLAY__CONFIG_WRAPPER(type, ...) (type) __VA_ARGS__
#endif

#define CLAY_LAYOUT(...) Clay__AttachLayoutConfig(Clay__StoreLayoutConfig(CLAY__CONFIG_WRAPPER(Clay_LayoutConfig, __VA_ARGS__)))

#define CLAY_RECTANGLE(...) Clay__AttachElementConfig(CLAY__CONFIG_WRAPPER(Clay_ElementConfigUnion, { .rectangleElementConfig = Clay__StoreRectangleElementConfig(CLAY__INIT(Clay_RectangleElementConfig) __VA_ARGS__) }, CLAY__ELEMENT_CONFIG_TYPE_RECTANGLE))

#define CLAY_TEXT_CONFIG(...) Clay__StoreTextElementConfig(CLAY__CONFIG_WRAPPER(Clay_TextElementConfig, __VA_ARGS__))

#define CLAY_IMAGE(...) Clay__AttachElementConfig(CLAY__CONFIG_WRAPPER(Clay_ElementConfigUnion, { .imageElementConfig = Clay__StoreImageElementConfig(CLAY__INIT(Clay_ImageElementConfig) __VA_ARGS__) }, CLAY__ELEMENT_CONFIG_TYPE_IMAGE))

#define CLAY_FLOATING(...) Clay__AttachElementConfig(CLAY__CONFIG_WRAPPER(Clay_ElementConfigUnion, { .floatingElementConfig = Clay__StoreFloatingElementConfig(CLAY__INIT(Clay_FloatingElementConfig) __VA_ARGS__) }, CLAY__ELEMENT_CONFIG_TYPE_FLOATING_CONTAINER))

#define CLAY_CUSTOM_ELEMENT(...) Clay__AttachElementConfig(CLAY__CONFIG_WRAPPER(Clay_ElementConfigUnion, { .customElementConfig = Clay__StoreCustomElementConfig(CLAY__INIT(Clay_CustomElementConfig) __VA_ARGS__) }, CLAY__ELEMENT_CONFIG_TYPE_CUSTOM))

#define CLAY_SCROLL(...) Clay__AttachElementConfig(CLAY__CONFIG_WRAPPER(Clay_ElementConfigUnion, { .scrollElementConfig = Clay__StoreScrollElementConfig(CLAY__INIT(Clay_ScrollElementConfig) __VA_ARGS__) }, CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER))

#define CLAY_BORDER(...) Clay__AttachElementConfig(CLAY__CONFIG_WRAPPER(Clay_ElementConfigUnion, { .borderElementConfig = Clay__StoreBorderElementConfig(CLAY__INIT(Clay_BorderElementConfig) __VA_ARGS__) }, CLAY__ELEMENT_CONFIG_TYPE_BORDER_CONTAINER))

#define CLAY_BORDER_OUTSIDE(...) Clay__AttachElementConfig(CLAY__CONFIG_WRAPPER(Clay_ElementConfigUnion, { .borderElementConfig = Clay__StoreBorderElementConfig(CLAY__INIT(Clay_BorderElementConfig) { .left = __VA_ARGS__, .right = __VA_ARGS__, .top = __VA_ARGS__, .bottom = __VA_ARGS__ }) }, CLAY__ELEMENT_CONFIG_TYPE_BORDER_CONTAINER))

#define CLAY_BORDER_OUTSIDE_RADIUS(width, color, radius) Clay__AttachElementConfig(CLAY__CONFIG_WRAPPER(Clay_ElementConfigUnion, { .borderElementConfig = Clay__StoreBorderElementConfig(CLAY__INIT(Clay_BorderElementConfig) { .left = { width, color }, .right = { width, color }, .top = { width, color }, .bottom = { width, color }, .cornerRadius = { radius, radius, radius, radius } })}, CLAY__ELEMENT_CONFIG_TYPE_BORDER_CONTAINER))

#define CLAY_BORDER_ALL(...) Clay__AttachElementConfig(CLAY__CONFIG_WRAPPER(Clay_ElementConfigUnion, { .borderElementConfig = Clay__StoreBorderElementConfig(CLAY__INIT(Clay_BorderElementConfig) { .left = __VA_ARGS__, .right = __VA_ARGS__, .top = __VA_ARGS__, .bottom = __VA_ARGS__, .betweenChildren = __VA_ARGS__ }) }, CLAY__ELEMENT_CONFIG_TYPE_BORDER_CONTAINER))

#define CLAY_BORDER_ALL_RADIUS(width, color, radius) Clay__AttachElementConfig(CLAY__CONFIG_WRAPPER(Clay_ElementConfigUnion, { .borderElementConfig = Clay__StoreBorderElementConfig(CLAY__INIT(Clay_BorderElementConfig) { .left = { width, color }, .right = { width, color }, .top = { width, color }, .bottom = { width, color }, .betweenChildren = { width, color }, .cornerRadius = { radius, radius, radius, radius }}) }))

#define CLAY_CORNER_RADIUS(radius) CLAY__INIT(Clay_CornerRadius) { radius, radius, radius, radius }

#define CLAY__STRUCT_1_ARGS(a) a
#define CLAY__STRUCT_0_ARGS() {}
#define CLAY__STRUCT_OVERRIDE(_0, _1, NAME, ...) NAME

#define CLAY__SIZING_FIT_INTERNAL(...) CLAY__INIT(Clay_SizingAxis) { .sizeMinMax = CLAY__INIT(Clay_SizingMinMax) __VA_ARGS__, .type = CLAY__SIZING_TYPE_FIT }
#define CLAY_SIZING_FIT(...) CLAY__SIZING_FIT_INTERNAL(CLAY__STRUCT_OVERRIDE("empty", ##__VA_ARGS__, CLAY__STRUCT_1_ARGS, CLAY__STRUCT_0_ARGS)(__VA_ARGS__))

#define CLAY__SIZING_GROW_INTERNAL(...) CLAY__INIT(Clay_SizingAxis) { .sizeMinMax = CLAY__INIT(Clay_SizingMinMax) __VA_ARGS__, .type = CLAY__SIZING_TYPE_GROW }
#define CLAY_SIZING_GROW(...) CLAY__SIZING_GROW_INTERNAL(CLAY__STRUCT_OVERRIDE("empty", ##__VA_ARGS__, CLAY__STRUCT_1_ARGS, CLAY__STRUCT_0_ARGS)(__VA_ARGS__))

#define CLAY_SIZING_FIXED(fixedSize) CLAY__INIT(Clay_SizingAxis) { .sizeMinMax = { fixedSize, fixedSize }, .type = CLAY__SIZING_TYPE_FIXED }

#define CLAY_SIZING_PERCENT(percentOfParent) CLAY__INIT(Clay_SizingAxis) { .sizePercent = (percentOfParent), .type = CLAY__SIZING_TYPE_PERCENT }

#define CLAY_ID(label) Clay__AttachId(Clay__HashString(CLAY_STRING(label), 0, 0))

#define CLAY_IDI(label, index) Clay__AttachId(Clay__HashString(CLAY_STRING(label), index, 0))

#define CLAY_ID_LOCAL(label) CLAY_IDI_LOCAL(label, 0)

#define CLAY_IDI_LOCAL(label, index) Clay__AttachId(Clay__HashString(CLAY_STRING(label), index, Clay__GetParentElementId()))

#define CLAY__STRING_LENGTH(s) ((sizeof(s) / sizeof((s)[0])) - sizeof((s)[0]))

#define CLAY_STRING(string) CLAY__INIT(Clay_String) { .length = CLAY__STRING_LENGTH(string), .chars = (string) }

static int CLAY__ELEMENT_DEFINITION_LATCH = 0;

#define CLAY__ELEMENT_INTERNAL(...) \
	for (\
		CLAY__ELEMENT_DEFINITION_LATCH = (Clay__OpenElement(), __VA_ARGS__, Clay__ElementPostConfiguration(), 0); \
		CLAY__ELEMENT_DEFINITION_LATCH < 1; \
		++CLAY__ELEMENT_DEFINITION_LATCH, Clay__CloseElement() \
	)

#define CLAY__6_ARGS(a, b, c, d, e, f) a, b, c, d, e, f
#define CLAY__5_ARGS(a, b, c, d, e) a, b, c, d, e
#define CLAY__4_ARGS(a, b, c, d) a, b, c, d
#define CLAY__3_ARGS(a, b, c) a, b, c
#define CLAY__2_ARGS(a, b) a, b
#define CLAY__1_ARGS(a) a
#define CLAY__0_ARGS() Clay__Noop()
#define CLAY__ARGS_OVERRIDE(_0, _1, _2, _3, _4, _5, _6, NAME, ...) NAME

// Publicly visible layout element macros -----------------------------------------------------
#define CLAY(...) CLAY__ELEMENT_INTERNAL(CLAY__ARGS_OVERRIDE("empty", ##__VA_ARGS__, CLAY__6_ARGS, CLAY__5_ARGS, CLAY__4_ARGS, CLAY__3_ARGS, CLAY__2_ARGS, CLAY__1_ARGS, CLAY__0_ARGS)(__VA_ARGS__))

#define CLAY_TEXT(text, textConfig) Clay__OpenTextElement(text, textConfig)

#ifdef __cplusplus
#define CLAY__INIT(type) type
#define CLAY__ALIGNMENT(type) alignof(type)
#define CLAY_PACKED_ENUM : uint8_t
#else
#define CLAY__INIT(type) (type)
#define CLAY__ALIGNMENT(type) (offsetof(struct { char c; type x; }, x))
#define CLAY_PACKED_ENUM __attribute__((__packed__))
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Utility Structs -------------------------
// Note: Clay_String is not guaranteed to be null terminated. It may be if created from a literal C string,
// but it is also used to represent slices.
typedef struct {
    int length;
    const char *chars;
} Clay_String;

typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay_String *internalArray;
} Clay__StringArray;

typedef struct {
    Clay_String label;
    uint64_t nextAllocation;
    uint64_t capacity;
    char *memory;
} Clay_Arena;

typedef struct {
    float width, height;
} Clay_Dimensions;

typedef struct {
    float x, y;
} Clay_Vector2;

typedef struct {
    float r, g, b, a;
} Clay_Color;

typedef struct {
    float x, y, width, height;
} Clay_BoundingBox;

// baseId + offset = id
typedef struct {
    uint32_t id;
    uint32_t offset;
    uint32_t baseId;
    Clay_String stringId;
} Clay_ElementId;

typedef struct {
    float topLeft;
    float topRight;
    float bottomLeft;
    float bottomRight;
} Clay_CornerRadius;

typedef enum CLAY_PACKED_ENUM {
    CLAY__ELEMENT_CONFIG_TYPE_RECTANGLE = 1,
    CLAY__ELEMENT_CONFIG_TYPE_BORDER_CONTAINER = 2,
    CLAY__ELEMENT_CONFIG_TYPE_FLOATING_CONTAINER = 4,
    CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER = 8,
    CLAY__ELEMENT_CONFIG_TYPE_IMAGE = 16,
    CLAY__ELEMENT_CONFIG_TYPE_TEXT = 32,
    CLAY__ELEMENT_CONFIG_TYPE_CUSTOM = 64,
} Clay__ElementConfigType;

// Element Configs ---------------------------
// Layout
typedef enum CLAY_PACKED_ENUM {
    CLAY_LEFT_TO_RIGHT,
    CLAY_TOP_TO_BOTTOM,
} Clay_LayoutDirection;

typedef enum CLAY_PACKED_ENUM {
    CLAY_ALIGN_X_LEFT,
    CLAY_ALIGN_X_RIGHT,
    CLAY_ALIGN_X_CENTER,
} Clay_LayoutAlignmentX;

typedef enum CLAY_PACKED_ENUM {
    CLAY_ALIGN_Y_TOP,
    CLAY_ALIGN_Y_BOTTOM,
    CLAY_ALIGN_Y_CENTER,
} Clay_LayoutAlignmentY;

typedef enum CLAY_PACKED_ENUM {
    CLAY__SIZING_TYPE_FIT,
    CLAY__SIZING_TYPE_GROW,
    CLAY__SIZING_TYPE_PERCENT,
    CLAY__SIZING_TYPE_FIXED,
} Clay__SizingType;

typedef struct {
    Clay_LayoutAlignmentX x;
    Clay_LayoutAlignmentY y;
} Clay_ChildAlignment;

typedef struct {
    float min;
    float max;
} Clay_SizingMinMax;

typedef struct {
    union {
        Clay_SizingMinMax sizeMinMax;
        float sizePercent;
    };
    Clay__SizingType type;
} Clay_SizingAxis;

typedef struct {
    Clay_SizingAxis width;
    Clay_SizingAxis height;
} Clay_Sizing;

typedef struct {
    uint16_t x;
    uint16_t y;
} Clay_Padding;

typedef struct {
    Clay_Sizing sizing;
    Clay_Padding padding;
    uint16_t childGap;
    Clay_ChildAlignment childAlignment;
    Clay_LayoutDirection layoutDirection;
} Clay_LayoutConfig;

extern Clay_LayoutConfig CLAY_LAYOUT_DEFAULT;

// Rectangle
typedef struct {
    Clay_Color color;
    Clay_CornerRadius cornerRadius;
    #ifdef CLAY_EXTEND_CONFIG_RECTANGLE
    CLAY_EXTEND_CONFIG_RECTANGLE
    #endif
} Clay_RectangleElementConfig;

// Text
typedef enum
{
    CLAY_TEXT_WRAP_WORDS,
    CLAY_TEXT_WRAP_NEWLINES,
    CLAY_TEXT_WRAP_NONE,
} Clay_TextElementConfigWrapMode;

typedef struct
{
    Clay_Color textColor;
    uint16_t fontId;
    uint16_t fontSize;
    uint16_t letterSpacing;
    uint16_t lineHeight;
    Clay_TextElementConfigWrapMode wrapMode;
    #ifdef CLAY_EXTEND_CONFIG_TEXT
    CLAY_EXTEND_CONFIG_TEXT
    #endif
} Clay_TextElementConfig;

// Image
typedef struct
{
    void * imageData;
    Clay_Dimensions sourceDimensions;
    #ifdef CLAY_EXTEND_CONFIG_IMAGE
    CLAY_EXTEND_CONFIG_IMAGE
    #endif
} Clay_ImageElementConfig;

// Floating
typedef enum CLAY_PACKED_ENUM {
    CLAY_ATTACH_POINT_LEFT_TOP,
    CLAY_ATTACH_POINT_LEFT_CENTER,
    CLAY_ATTACH_POINT_LEFT_BOTTOM,
    CLAY_ATTACH_POINT_CENTER_TOP,
    CLAY_ATTACH_POINT_CENTER_CENTER,
    CLAY_ATTACH_POINT_CENTER_BOTTOM,
    CLAY_ATTACH_POINT_RIGHT_TOP,
    CLAY_ATTACH_POINT_RIGHT_CENTER,
    CLAY_ATTACH_POINT_RIGHT_BOTTOM,
} Clay_FloatingAttachPointType;

typedef struct
{
    Clay_FloatingAttachPointType element;
    Clay_FloatingAttachPointType parent;
} Clay_FloatingAttachPoints;

typedef struct
{
    Clay_Vector2 offset;
    Clay_Dimensions expand;
    uint16_t zIndex;
    uint32_t parentId;
    Clay_FloatingAttachPoints attachment;
} Clay_FloatingElementConfig;

// Custom
typedef struct
{
    #ifndef CLAY_EXTEND_CONFIG_CUSTOM
    void* customData;
    #else
    CLAY_EXTEND_CONFIG_CUSTOM
    #endif
} Clay_CustomElementConfig;

// Scroll
typedef struct
{
    bool horizontal;
    bool vertical;
} Clay_ScrollElementConfig;

// Border
typedef struct
{
    uint32_t width;
    Clay_Color color;
} Clay_Border;

typedef struct
{
    Clay_Border left;
    Clay_Border right;
    Clay_Border top;
    Clay_Border bottom;
    Clay_Border betweenChildren;
    Clay_CornerRadius cornerRadius;
} Clay_BorderElementConfig;

typedef union
{
    Clay_RectangleElementConfig *rectangleElementConfig;
    Clay_TextElementConfig *textElementConfig;
    Clay_ImageElementConfig *imageElementConfig;
    Clay_FloatingElementConfig *floatingElementConfig;
    Clay_CustomElementConfig *customElementConfig;
    Clay_ScrollElementConfig *scrollElementConfig;
    Clay_BorderElementConfig *borderElementConfig;
} Clay_ElementConfigUnion;

typedef struct
{
    Clay__ElementConfigType type;
    Clay_ElementConfigUnion config;
} Clay_ElementConfig;

// Miscellaneous Structs & Enums ---------------------------------
typedef struct
{
    // Note: This is a pointer to the real internal scroll position, mutating it may cause a change in final layout.
    // Intended for use with external functionality that modifies scroll position, such as scroll bars or auto scrolling.
    Clay_Vector2 *scrollPosition;
    Clay_Dimensions scrollContainerDimensions;
    Clay_Dimensions contentDimensions;
    Clay_ScrollElementConfig config;
    // Indicates whether an actual scroll container matched the provided ID or if the default struct was returned.
    bool found;
} Clay_ScrollContainerData;

typedef enum {
    CLAY_RENDER_COMMAND_TYPE_NONE,
    CLAY_RENDER_COMMAND_TYPE_RECTANGLE,
    CLAY_RENDER_COMMAND_TYPE_BORDER,
    CLAY_RENDER_COMMAND_TYPE_TEXT,
    CLAY_RENDER_COMMAND_TYPE_IMAGE,
    CLAY_RENDER_COMMAND_TYPE_SCISSOR_START,
    CLAY_RENDER_COMMAND_TYPE_SCISSOR_END,
    CLAY_RENDER_COMMAND_TYPE_CUSTOM,
} Clay_RenderCommandType;

typedef struct
{
    Clay_BoundingBox boundingBox;
    Clay_ElementConfigUnion config;
    Clay_String text; // TODO I wish there was a way to avoid having to have this on every render command
    uint32_t id;
    Clay_RenderCommandType commandType;
    #ifdef CLAY_DEBUG
    Clay_String name;
    #endif
} Clay_RenderCommand;

typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay_RenderCommand *internalArray;
} Clay_RenderCommandArray;

typedef enum
{
    CLAY_POINTER_DATA_PRESSED_THIS_FRAME,
    CLAY_POINTER_DATA_PRESSED,
    CLAY_POINTER_DATA_RELEASED_THIS_FRAME,
    CLAY_POINTER_DATA_RELEASED,
} Clay_PointerDataInteractionState;

typedef struct
{
    Clay_Vector2 position;
    Clay_PointerDataInteractionState state;
} Clay_PointerData;

// Function Forward Declarations ---------------------------------
// Public API functions ---
uint32_t Clay_MinMemorySize();
Clay_Arena Clay_CreateArenaWithCapacityAndMemory(uint32_t capacity, void *offset);
void Clay_SetPointerState(Clay_Vector2 position, bool pointerDown);
void Clay_Initialize(Clay_Arena arena, Clay_Dimensions layoutDimensions);
void Clay_UpdateScrollContainers(bool enableDragScrolling, Clay_Vector2 scrollDelta, float deltaTime);
void Clay_SetLayoutDimensions(Clay_Dimensions dimensions);
void Clay_BeginLayout();
Clay_RenderCommandArray Clay_EndLayout();
Clay_ElementId Clay_GetElementId(Clay_String idString);
Clay_ElementId Clay_GetElementIdWithIndex(Clay_String idString, uint32_t index);
bool Clay_Hovered();
void Clay_OnHover(void (*onHoverFunction)(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData), intptr_t userData);
Clay_ScrollContainerData Clay_GetScrollContainerData(Clay_ElementId id);
void Clay_SetMeasureTextFunction(Clay_Dimensions (*measureTextFunction)(Clay_String *text, Clay_TextElementConfig *config));
Clay_RenderCommand * Clay_RenderCommandArray_Get(Clay_RenderCommandArray* array, int32_t index);
void Clay_SetDebugModeEnabled(bool enabled);

// Internal API functions required by macros
void Clay__OpenElement();
void Clay__CloseElement();
Clay_LayoutConfig * Clay__StoreLayoutConfig(Clay_LayoutConfig config);
void Clay__ElementPostConfiguration();
void Clay__AttachId(Clay_ElementId id);
void Clay__AttachLayoutConfig(Clay_LayoutConfig *config);
void Clay__AttachElementConfig(Clay_ElementConfigUnion config, Clay__ElementConfigType type);
Clay_RectangleElementConfig * Clay__StoreRectangleElementConfig(Clay_RectangleElementConfig config);
Clay_TextElementConfig * Clay__StoreTextElementConfig(Clay_TextElementConfig config);
Clay_ImageElementConfig * Clay__StoreImageElementConfig(Clay_ImageElementConfig config);
Clay_FloatingElementConfig * Clay__StoreFloatingElementConfig(Clay_FloatingElementConfig config);
Clay_CustomElementConfig * Clay__StoreCustomElementConfig(Clay_CustomElementConfig config);
Clay_ScrollElementConfig * Clay__StoreScrollElementConfig(Clay_ScrollElementConfig config);
Clay_BorderElementConfig * Clay__StoreBorderElementConfig(Clay_BorderElementConfig config);
Clay_ElementId Clay__HashString(Clay_String key, uint32_t offset, uint32_t seed);
void Clay__Noop();
void Clay__OpenTextElement(Clay_String text, Clay_TextElementConfig *textConfig);
uint32_t Clay__GetParentElementId(void);

extern Clay_Color Clay__debugViewHighlightColor;
extern uint32_t Clay__debugViewWidth;

#ifdef __cplusplus
}
#endif

#endif

// -----------------------------------------
// IMPLEMENTATION --------------------------
// -----------------------------------------
#ifdef CLAY_IMPLEMENTATION
#undef CLAY_IMPLEMENTATION

#ifdef CLAY_OVERFLOW_TRAP
    #include "signal.h"
#endif

#ifndef CLAY_MAX_ELEMENT_COUNT
#define CLAY_MAX_ELEMENT_COUNT 8192
#endif

#ifndef CLAY__NULL
#define CLAY__NULL 0
#endif

#ifndef CLAY__MAXFLOAT
#define CLAY__MAXFLOAT 3.40282346638528859812e+38F
#endif

#define CLAY__MAX(x, y) (((x) > (y)) ? (x) : (y))
#define CLAY__MIN(x, y) (((x) < (y)) ? (x) : (y))

bool Clay__warningsEnabled = true;

void Clay__Noop() {};

Clay_String CLAY__SPACECHAR = CLAY__INIT(Clay_String) { .length = 1, .chars = " " };
Clay_String CLAY__STRING_DEFAULT = CLAY__INIT(Clay_String) { .length = 0, .chars = NULL };

typedef struct
{
    Clay_String baseMessage;
    Clay_String dynamicMessage;
} Clay__Warning;

Clay__Warning CLAY__WARNING_DEFAULT = CLAY__INIT(Clay__Warning) {};

#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay__Warning *internalArray;
} Clay__WarningArray;

Clay__WarningArray Clay__WarningArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    uint64_t totalSizeBytes = capacity * sizeof(Clay_String);
    Clay__WarningArray array = CLAY__INIT(Clay__WarningArray){.capacity = capacity, .length = 0};
    uint64_t nextAllocAddress = (uint64_t)arena->nextAllocation + (uint64_t)arena->memory;
    uint64_t arenaOffsetAligned = nextAllocAddress + (CLAY__ALIGNMENT(Clay_String) - (nextAllocAddress % CLAY__ALIGNMENT(Clay_String)));
    arenaOffsetAligned -= (uint64_t)arena->memory;
    if (arenaOffsetAligned + totalSizeBytes <= arena->capacity) {
        array.internalArray = (Clay__Warning*)((uint64_t)arena->memory + (uint64_t)arenaOffsetAligned);
        arena->nextAllocation = arenaOffsetAligned + totalSizeBytes;
    }
    else {
        #ifdef CLAY_OVERFLOW_TRAP
        raise(SIGTRAP);
        #endif
    }
    return array;
}

Clay__WarningArray Clay_warnings = CLAY__INIT(Clay__WarningArray) {};

Clay__Warning *Clay__WarningArray_Add(Clay__WarningArray *array, Clay__Warning item)
{
    if (array->length < array->capacity) {
        array->internalArray[array->length++] = item;
        return &array->internalArray[array->length - 1];
    }
    else {
        #ifdef CLAY_OVERFLOW_TRAP
        raise(SIGTRAP);
        #endif
    }
    return &CLAY__WARNING_DEFAULT;
}

void* Clay__Array_Allocate_Arena(uint32_t capacity, uint32_t itemSize, uint32_t alignment, Clay_Arena *arena)
{
    uint64_t totalSizeBytes = capacity * itemSize;
    uint64_t nextAllocAddress = (uint64_t)arena->nextAllocation + (uint64_t)arena->memory;
    uint64_t arenaOffsetAligned = nextAllocAddress + (alignment - (nextAllocAddress % alignment));
    arenaOffsetAligned -= (uint64_t)arena->memory;
    if (arenaOffsetAligned + totalSizeBytes <= arena->capacity) {
        arena->nextAllocation = arenaOffsetAligned + totalSizeBytes;
        return (void*)((uint64_t)arena->memory + (uint64_t)arenaOffsetAligned);
    }
    else {
        if (Clay__warningsEnabled) {
            Clay__WarningArray_Add(&Clay_warnings, CLAY__INIT(Clay__Warning) { CLAY_STRING("Attempting to allocate array in arena, but arena is already at capacity and would overflow.") });
        }
        #ifdef CLAY_OVERFLOW_TRAP
        raise(SIGTRAP);
        #endif
    }
    return CLAY__NULL;
}

bool Clay__Array_RangeCheck(int index, uint32_t length)
{
    if (index < length && index >= 0) {
        return true;
    }
    if (Clay__warningsEnabled) {
        Clay__WarningArray_Add(&Clay_warnings, CLAY__INIT(Clay__Warning) { CLAY_STRING("Array access out of bounds.") });
    }
    #ifdef CLAY_OVERFLOW_TRAP
    raise(SIGTRAP);
    #endif
    return false;
}

bool Clay__Array_IncrementCapacityCheck(uint32_t length, uint32_t capacity)
{
    if (length < capacity) {
        return true;
    }
    if (Clay__warningsEnabled) {
        Clay__WarningArray_Add(&Clay_warnings, CLAY__INIT(Clay__Warning) { CLAY_STRING("Attempting to add to array that is already at capacity.") });
    }
    #ifdef CLAY_OVERFLOW_TRAP
    raise(SIGTRAP);
    #endif
    return false;
}

bool CLAY__BOOL_DEFAULT = false;

// __GENERATED__ template array_define,array_allocate TYPE=bool NAME=Clay__BoolArray
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	bool *internalArray;
} Clay__BoolArray;
Clay__BoolArray Clay__BoolArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__BoolArray){.capacity = capacity, .length = 0, .internalArray = (bool *)Clay__Array_Allocate_Arena(capacity, sizeof(bool), CLAY__ALIGNMENT(bool), arena)};
}
#pragma endregion
// __GENERATED__ template

Clay_ElementId CLAY__ELEMENT_ID_DEFAULT = CLAY__INIT(Clay_ElementId) {};

// __GENERATED__ template array_define,array_allocate,array_get,array_add TYPE=Clay_ElementId NAME=Clay__ElementIdArray DEFAULT_VALUE=&CLAY__ELEMENT_ID_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay_ElementId *internalArray;
} Clay__ElementIdArray;
Clay__ElementIdArray Clay__ElementIdArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__ElementIdArray){.capacity = capacity, .length = 0, .internalArray = (Clay_ElementId *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay_ElementId), CLAY__ALIGNMENT(Clay_ElementId), arena)};
}
Clay_ElementId *Clay__ElementIdArray_Get(Clay__ElementIdArray *array, int index) {
    return Clay__Array_RangeCheck(index, array->length) ? &array->internalArray[index] : &CLAY__ELEMENT_ID_DEFAULT;
}
Clay_ElementId *Clay__ElementIdArray_Add(Clay__ElementIdArray *array, Clay_ElementId item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__ELEMENT_ID_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

Clay_ElementConfig CLAY__ELEMENT_CONFIG_DEFAULT = CLAY__INIT(Clay_ElementConfig) {};

// __GENERATED__ template array_define,array_define_slice,array_allocate,array_get,array_add,array_get_slice TYPE=Clay_ElementConfig NAME=Clay__ElementConfigArray DEFAULT_VALUE=&CLAY__ELEMENT_CONFIG_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay_ElementConfig *internalArray;
} Clay__ElementConfigArray;
typedef struct
{
	uint32_t length;
	Clay_ElementConfig *internalArray;
} Clay__ElementConfigArraySlice;
Clay__ElementConfigArray Clay__ElementConfigArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__ElementConfigArray){.capacity = capacity, .length = 0, .internalArray = (Clay_ElementConfig *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay_ElementConfig), CLAY__ALIGNMENT(Clay_ElementConfig), arena)};
}
Clay_ElementConfig *Clay__ElementConfigArray_Get(Clay__ElementConfigArray *array, int index) {
    return Clay__Array_RangeCheck(index, array->length) ? &array->internalArray[index] : &CLAY__ELEMENT_CONFIG_DEFAULT;
}
Clay_ElementConfig *Clay__ElementConfigArray_Add(Clay__ElementConfigArray *array, Clay_ElementConfig item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__ELEMENT_CONFIG_DEFAULT;
}
Clay_ElementConfig *Clay__ElementConfigArraySlice_Get(Clay__ElementConfigArraySlice *slice, int index) {
    return Clay__Array_RangeCheck(index, slice->length) ? &slice->internalArray[index] : &CLAY__ELEMENT_CONFIG_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

Clay_LayoutConfig CLAY_LAYOUT_DEFAULT = CLAY__INIT(Clay_LayoutConfig){ .sizing = { .width = { .sizeMinMax = {0, CLAY__MAXFLOAT }, .type = CLAY__SIZING_TYPE_FIT }, .height = { .sizeMinMax = {0, CLAY__MAXFLOAT }, .type = CLAY__SIZING_TYPE_FIT } } };

// __GENERATED__ template array_define,array_allocate,array_add TYPE=Clay_LayoutConfig NAME=Clay__LayoutConfigArray DEFAULT_VALUE=&CLAY_LAYOUT_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay_LayoutConfig *internalArray;
} Clay__LayoutConfigArray;
Clay__LayoutConfigArray Clay__LayoutConfigArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__LayoutConfigArray){.capacity = capacity, .length = 0, .internalArray = (Clay_LayoutConfig *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay_LayoutConfig), CLAY__ALIGNMENT(Clay_LayoutConfig), arena)};
}
Clay_LayoutConfig *Clay__LayoutConfigArray_Add(Clay__LayoutConfigArray *array, Clay_LayoutConfig item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY_LAYOUT_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

Clay_RectangleElementConfig CLAY__RECTANGLE_ELEMENT_CONFIG_DEFAULT = CLAY__INIT(Clay_RectangleElementConfig){{0}};

// __GENERATED__ template array_define,array_allocate,array_add TYPE=Clay_RectangleElementConfig NAME=Clay__RectangleElementConfigArray DEFAULT_VALUE=&CLAY__RECTANGLE_ELEMENT_CONFIG_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay_RectangleElementConfig *internalArray;
} Clay__RectangleElementConfigArray;
Clay__RectangleElementConfigArray Clay__RectangleElementConfigArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__RectangleElementConfigArray){.capacity = capacity, .length = 0, .internalArray = (Clay_RectangleElementConfig *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay_RectangleElementConfig), CLAY__ALIGNMENT(Clay_RectangleElementConfig), arena)};
}
Clay_RectangleElementConfig *Clay__RectangleElementConfigArray_Add(Clay__RectangleElementConfigArray *array, Clay_RectangleElementConfig item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__RECTANGLE_ELEMENT_CONFIG_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

Clay_TextElementConfig CLAY__TEXT_ELEMENT_CONFIG_DEFAULT = CLAY__INIT(Clay_TextElementConfig) {};

// __GENERATED__ template array_define,array_allocate,array_add TYPE=Clay_TextElementConfig NAME=Clay__TextElementConfigArray DEFAULT_VALUE=&CLAY__TEXT_ELEMENT_CONFIG_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay_TextElementConfig *internalArray;
} Clay__TextElementConfigArray;
Clay__TextElementConfigArray Clay__TextElementConfigArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__TextElementConfigArray){.capacity = capacity, .length = 0, .internalArray = (Clay_TextElementConfig *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay_TextElementConfig), CLAY__ALIGNMENT(Clay_TextElementConfig), arena)};
}
Clay_TextElementConfig *Clay__TextElementConfigArray_Add(Clay__TextElementConfigArray *array, Clay_TextElementConfig item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__TEXT_ELEMENT_CONFIG_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

Clay_ImageElementConfig CLAY__IMAGE_ELEMENT_CONFIG_DEFAULT = CLAY__INIT(Clay_ImageElementConfig) {};

// __GENERATED__ template array_define,array_allocate,array_add TYPE=Clay_ImageElementConfig NAME=Clay__ImageElementConfigArray DEFAULT_VALUE=&CLAY__IMAGE_ELEMENT_CONFIG_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay_ImageElementConfig *internalArray;
} Clay__ImageElementConfigArray;
Clay__ImageElementConfigArray Clay__ImageElementConfigArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__ImageElementConfigArray){.capacity = capacity, .length = 0, .internalArray = (Clay_ImageElementConfig *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay_ImageElementConfig), CLAY__ALIGNMENT(Clay_ImageElementConfig), arena)};
}
Clay_ImageElementConfig *Clay__ImageElementConfigArray_Add(Clay__ImageElementConfigArray *array, Clay_ImageElementConfig item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__IMAGE_ELEMENT_CONFIG_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

Clay_FloatingElementConfig CLAY__FLOATING_ELEMENT_CONFIG_DEFAULT = CLAY__INIT(Clay_FloatingElementConfig) {};

// __GENERATED__ template array_define,array_allocate,array_add TYPE=Clay_FloatingElementConfig NAME=Clay__FloatingElementConfigArray DEFAULT_VALUE=&CLAY__FLOATING_ELEMENT_CONFIG_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay_FloatingElementConfig *internalArray;
} Clay__FloatingElementConfigArray;
Clay__FloatingElementConfigArray Clay__FloatingElementConfigArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__FloatingElementConfigArray){.capacity = capacity, .length = 0, .internalArray = (Clay_FloatingElementConfig *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay_FloatingElementConfig), CLAY__ALIGNMENT(Clay_FloatingElementConfig), arena)};
}
Clay_FloatingElementConfig *Clay__FloatingElementConfigArray_Add(Clay__FloatingElementConfigArray *array, Clay_FloatingElementConfig item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__FLOATING_ELEMENT_CONFIG_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

Clay_CustomElementConfig CLAY__CUSTOM_ELEMENT_CONFIG_DEFAULT = CLAY__INIT(Clay_CustomElementConfig) {};

// __GENERATED__ template array_define,array_allocate,array_add TYPE=Clay_CustomElementConfig NAME=Clay__CustomElementConfigArray DEFAULT_VALUE=&CLAY__CUSTOM_ELEMENT_CONFIG_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay_CustomElementConfig *internalArray;
} Clay__CustomElementConfigArray;
Clay__CustomElementConfigArray Clay__CustomElementConfigArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__CustomElementConfigArray){.capacity = capacity, .length = 0, .internalArray = (Clay_CustomElementConfig *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay_CustomElementConfig), CLAY__ALIGNMENT(Clay_CustomElementConfig), arena)};
}
Clay_CustomElementConfig *Clay__CustomElementConfigArray_Add(Clay__CustomElementConfigArray *array, Clay_CustomElementConfig item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__CUSTOM_ELEMENT_CONFIG_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

Clay_ScrollElementConfig CLAY__SCROLL_CONTAINER_ELEMENT_CONFIG_DEFAULT = CLAY__INIT(Clay_ScrollElementConfig ) {};

// __GENERATED__ template array_define,array_allocate,array_add TYPE=Clay_ScrollElementConfig NAME=Clay__ScrollElementConfigArray DEFAULT_VALUE=&CLAY__SCROLL_CONTAINER_ELEMENT_CONFIG_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay_ScrollElementConfig *internalArray;
} Clay__ScrollElementConfigArray;
Clay__ScrollElementConfigArray Clay__ScrollElementConfigArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__ScrollElementConfigArray){.capacity = capacity, .length = 0, .internalArray = (Clay_ScrollElementConfig *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay_ScrollElementConfig), CLAY__ALIGNMENT(Clay_ScrollElementConfig), arena)};
}
Clay_ScrollElementConfig *Clay__ScrollElementConfigArray_Add(Clay__ScrollElementConfigArray *array, Clay_ScrollElementConfig item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__SCROLL_CONTAINER_ELEMENT_CONFIG_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

// __GENERATED__ template array_define_slice,array_allocate,array_add TYPE=Clay_String NAME=Clay__StringArray DEFAULT_VALUE=&CLAY__STRING_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t length;
	Clay_String *internalArray;
} Clay__StringArraySlice;
Clay__StringArray Clay__StringArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__StringArray){.capacity = capacity, .length = 0, .internalArray = (Clay_String *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay_String), CLAY__ALIGNMENT(Clay_String), arena)};
}
Clay_String *Clay__StringArray_Add(Clay__StringArray *array, Clay_String item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__STRING_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

typedef struct
{
    Clay_String text;
    Clay_Dimensions preferredDimensions;
    uint32_t elementIndex;
    Clay__StringArraySlice wrappedLines;
} Clay__TextElementData;

Clay__TextElementData CLAY__TEXT_ELEMENT_DATA_DEFAULT = CLAY__INIT(Clay__TextElementData) {};

// __GENERATED__ template array_define,array_allocate,array_get,array_add TYPE=Clay__TextElementData NAME=Clay__TextElementDataArray DEFAULT_VALUE=&CLAY__TEXT_ELEMENT_DATA_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay__TextElementData *internalArray;
} Clay__TextElementDataArray;
Clay__TextElementDataArray Clay__TextElementDataArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__TextElementDataArray){.capacity = capacity, .length = 0, .internalArray = (Clay__TextElementData *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay__TextElementData), CLAY__ALIGNMENT(Clay__TextElementData), arena)};
}
Clay__TextElementData *Clay__TextElementDataArray_Get(Clay__TextElementDataArray *array, int index) {
    return Clay__Array_RangeCheck(index, array->length) ? &array->internalArray[index] : &CLAY__TEXT_ELEMENT_DATA_DEFAULT;
}
Clay__TextElementData *Clay__TextElementDataArray_Add(Clay__TextElementDataArray *array, Clay__TextElementData item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__TEXT_ELEMENT_DATA_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

Clay_BorderElementConfig CLAY__BORDER_CONTAINER_ELEMENT_CONFIG_DEFAULT = CLAY__INIT(Clay_BorderElementConfig ) {};

// __GENERATED__ template array_define,array_allocate,array_add TYPE=Clay_BorderElementConfig NAME=Clay__BorderElementConfigArray DEFAULT_VALUE=&CLAY__BORDER_CONTAINER_ELEMENT_CONFIG_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay_BorderElementConfig *internalArray;
} Clay__BorderElementConfigArray;
Clay__BorderElementConfigArray Clay__BorderElementConfigArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__BorderElementConfigArray){.capacity = capacity, .length = 0, .internalArray = (Clay_BorderElementConfig *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay_BorderElementConfig), CLAY__ALIGNMENT(Clay_BorderElementConfig), arena)};
}
Clay_BorderElementConfig *Clay__BorderElementConfigArray_Add(Clay__BorderElementConfigArray *array, Clay_BorderElementConfig item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__BORDER_CONTAINER_ELEMENT_CONFIG_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

typedef struct
{
    int32_t *elements;
    uint16_t length;
} Clay__LayoutElementChildren;

typedef struct
{
    #ifdef CLAY_DEBUG
    Clay_String name;
    #endif
    union {
        Clay__LayoutElementChildren children;
        Clay__TextElementData *textElementData;
    };
    Clay_Dimensions dimensions;
    Clay_Dimensions minDimensions;
    Clay_LayoutConfig *layoutConfig;
    Clay__ElementConfigArraySlice elementConfigs;
    uint32_t configsEnabled;
    uint32_t id;
} Clay_LayoutElement;

Clay_LayoutElement CLAY__LAYOUT_ELEMENT_DEFAULT = CLAY__INIT(Clay_LayoutElement) {};

// __GENERATED__ template array_define,array_allocate,array_add,array_get TYPE=Clay_LayoutElement NAME=Clay_LayoutElementArray DEFAULT_VALUE=&CLAY__LAYOUT_ELEMENT_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay_LayoutElement *internalArray;
} Clay_LayoutElementArray;
Clay_LayoutElementArray Clay_LayoutElementArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay_LayoutElementArray){.capacity = capacity, .length = 0, .internalArray = (Clay_LayoutElement *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay_LayoutElement), CLAY__ALIGNMENT(Clay_LayoutElement), arena)};
}
Clay_LayoutElement *Clay_LayoutElementArray_Add(Clay_LayoutElementArray *array, Clay_LayoutElement item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__LAYOUT_ELEMENT_DEFAULT;
}
Clay_LayoutElement *Clay_LayoutElementArray_Get(Clay_LayoutElementArray *array, int index) {
    return Clay__Array_RangeCheck(index, array->length) ? &array->internalArray[index] : &CLAY__LAYOUT_ELEMENT_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

// __GENERATED__ template array_define,array_allocate,array_add,array_get_value,array_remove_swapback TYPE=Clay_LayoutElement* NAME=Clay__LayoutElementPointerArray DEFAULT_VALUE=CLAY__NULL
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay_LayoutElement* *internalArray;
} Clay__LayoutElementPointerArray;
Clay__LayoutElementPointerArray Clay__LayoutElementPointerArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__LayoutElementPointerArray){.capacity = capacity, .length = 0, .internalArray = (Clay_LayoutElement* *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay_LayoutElement*), CLAY__ALIGNMENT(Clay_LayoutElement*), arena)};
}
Clay_LayoutElement* *Clay__LayoutElementPointerArray_Add(Clay__LayoutElementPointerArray *array, Clay_LayoutElement* item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return CLAY__NULL;
}
Clay_LayoutElement* Clay__LayoutElementPointerArray_Get(Clay__LayoutElementPointerArray *array, int index) {
    return Clay__Array_RangeCheck(index, array->length) ? array->internalArray[index] : CLAY__NULL;
}
Clay_LayoutElement* Clay__LayoutElementPointerArray_RemoveSwapback(Clay__LayoutElementPointerArray *array, int index) {
	if (Clay__Array_RangeCheck(index, array->length)) {
		array->length--;
		Clay_LayoutElement* removed = array->internalArray[index];
		array->internalArray[index] = array->internalArray[array->length];
		return removed;
	}
	return CLAY__NULL;
}
#pragma endregion
// __GENERATED__ template

Clay_RenderCommand CLAY__RENDER_COMMAND_DEFAULT = CLAY__INIT(Clay_RenderCommand) {};

// __GENERATED__ template array_allocate,array_add,array_get TYPE=Clay_RenderCommand NAME=Clay_RenderCommandArray DEFAULT_VALUE=&CLAY__RENDER_COMMAND_DEFAULT
#pragma region generated
Clay_RenderCommandArray Clay_RenderCommandArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay_RenderCommandArray){.capacity = capacity, .length = 0, .internalArray = (Clay_RenderCommand *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay_RenderCommand), CLAY__ALIGNMENT(Clay_RenderCommand), arena)};
}
Clay_RenderCommand *Clay_RenderCommandArray_Add(Clay_RenderCommandArray *array, Clay_RenderCommand item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__RENDER_COMMAND_DEFAULT;
}
Clay_RenderCommand *Clay_RenderCommandArray_Get(Clay_RenderCommandArray *array, int index) {
    return Clay__Array_RangeCheck(index, array->length) ? &array->internalArray[index] : &CLAY__RENDER_COMMAND_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

typedef struct
{
    Clay_LayoutElement *layoutElement;
    Clay_BoundingBox boundingBox;
    Clay_Dimensions contentSize;
    Clay_Vector2 scrollOrigin;
    Clay_Vector2 pointerOrigin;
    Clay_Vector2 scrollMomentum;
    Clay_Vector2 scrollPosition;
    Clay_Vector2 previousDelta;
    float momentumTime;
    uint32_t elementId;
    bool openThisFrame;
    bool pointerScrollActive;
} Clay__ScrollContainerDataInternal;

Clay__ScrollContainerDataInternal CLAY__SCROLL_CONTAINER_DEFAULT = CLAY__INIT(Clay__ScrollContainerDataInternal) {};

// __GENERATED__ template array_define,array_allocate,array_add,array_get TYPE=Clay__ScrollContainerDataInternal NAME=Clay__ScrollContainerDataInternalArray DEFAULT_VALUE=&CLAY__SCROLL_CONTAINER_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay__ScrollContainerDataInternal *internalArray;
} Clay__ScrollContainerDataInternalArray;
Clay__ScrollContainerDataInternalArray Clay__ScrollContainerDataInternalArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__ScrollContainerDataInternalArray){.capacity = capacity, .length = 0, .internalArray = (Clay__ScrollContainerDataInternal *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay__ScrollContainerDataInternal), CLAY__ALIGNMENT(Clay__ScrollContainerDataInternal), arena)};
}
Clay__ScrollContainerDataInternal *Clay__ScrollContainerDataInternalArray_Add(Clay__ScrollContainerDataInternalArray *array, Clay__ScrollContainerDataInternal item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__SCROLL_CONTAINER_DEFAULT;
}
Clay__ScrollContainerDataInternal *Clay__ScrollContainerDataInternalArray_Get(Clay__ScrollContainerDataInternalArray *array, int index) {
    return Clay__Array_RangeCheck(index, array->length) ? &array->internalArray[index] : &CLAY__SCROLL_CONTAINER_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

// __GENERATED__ template array_remove_swapback TYPE=Clay__ScrollContainerDataInternal NAME=Clay__ScrollContainerDataInternalArray DEFAULT_VALUE=CLAY__SCROLL_CONTAINER_DEFAULT
#pragma region generated
Clay__ScrollContainerDataInternal Clay__ScrollContainerDataInternalArray_RemoveSwapback(Clay__ScrollContainerDataInternalArray *array, int index) {
	if (Clay__Array_RangeCheck(index, array->length)) {
		array->length--;
		Clay__ScrollContainerDataInternal removed = array->internalArray[index];
		array->internalArray[index] = array->internalArray[array->length];
		return removed;
	}
	return CLAY__SCROLL_CONTAINER_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

typedef struct
{
    bool collision;
    bool collapsed;
} Clay__DebugElementData;

Clay__DebugElementData CLAY__DEBUG_ELEMENT_DATA_DEFAULT = CLAY__INIT(Clay__DebugElementData) {};

// __GENERATED__ template array_define,array_allocate,array_add,array_get TYPE=Clay__DebugElementData NAME=Clay__DebugElementDataArray DEFAULT_VALUE=&CLAY__DEBUG_ELEMENT_DATA_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay__DebugElementData *internalArray;
} Clay__DebugElementDataArray;
Clay__DebugElementDataArray Clay__DebugElementDataArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__DebugElementDataArray){.capacity = capacity, .length = 0, .internalArray = (Clay__DebugElementData *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay__DebugElementData), CLAY__ALIGNMENT(Clay__DebugElementData), arena)};
}
Clay__DebugElementData *Clay__DebugElementDataArray_Add(Clay__DebugElementDataArray *array, Clay__DebugElementData item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__DEBUG_ELEMENT_DATA_DEFAULT;
}
Clay__DebugElementData *Clay__DebugElementDataArray_Get(Clay__DebugElementDataArray *array, int index) {
    return Clay__Array_RangeCheck(index, array->length) ? &array->internalArray[index] : &CLAY__DEBUG_ELEMENT_DATA_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

typedef struct // todo get this struct into a single cache line
{
    Clay_BoundingBox boundingBox;
    Clay_ElementId elementId;
    Clay_LayoutElement* layoutElement;
    void (*onHoverFunction)(Clay_ElementId elementId, Clay_PointerData pointerInfo, intptr_t userData);
    intptr_t hoverFunctionUserData;
    int32_t nextIndex;
    uint32_t generation;
    Clay__DebugElementData *debugData;
} Clay_LayoutElementHashMapItem;

Clay_LayoutElementHashMapItem CLAY__LAYOUT_ELEMENT_HASH_MAP_ITEM_DEFAULT = CLAY__INIT(Clay_LayoutElementHashMapItem) { .layoutElement = &CLAY__LAYOUT_ELEMENT_DEFAULT };

// __GENERATED__ template array_define,array_allocate,array_get,array_add TYPE=Clay_LayoutElementHashMapItem NAME=Clay__LayoutElementHashMapItemArray DEFAULT_VALUE=&CLAY__LAYOUT_ELEMENT_HASH_MAP_ITEM_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay_LayoutElementHashMapItem *internalArray;
} Clay__LayoutElementHashMapItemArray;
Clay__LayoutElementHashMapItemArray Clay__LayoutElementHashMapItemArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__LayoutElementHashMapItemArray){.capacity = capacity, .length = 0, .internalArray = (Clay_LayoutElementHashMapItem *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay_LayoutElementHashMapItem), CLAY__ALIGNMENT(Clay_LayoutElementHashMapItem), arena)};
}
Clay_LayoutElementHashMapItem *Clay__LayoutElementHashMapItemArray_Get(Clay__LayoutElementHashMapItemArray *array, int index) {
    return Clay__Array_RangeCheck(index, array->length) ? &array->internalArray[index] : &CLAY__LAYOUT_ELEMENT_HASH_MAP_ITEM_DEFAULT;
}
Clay_LayoutElementHashMapItem *Clay__LayoutElementHashMapItemArray_Add(Clay__LayoutElementHashMapItemArray *array, Clay_LayoutElementHashMapItem item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__LAYOUT_ELEMENT_HASH_MAP_ITEM_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

typedef struct
{
    Clay_String word;
    uint32_t startOffset;
    uint32_t length;
    float width;
} Clay__MeasuredWord;

Clay__MeasuredWord CLAY__MEASURED_WORD_DEFAULT = CLAY__INIT(Clay__MeasuredWord) {};

// __GENERATED__ template array_define,array_define_slice,array_allocate,array_get,array_get_slice,array_add TYPE=Clay__MeasuredWord NAME=Clay__MeasuredWordArray DEFAULT_VALUE=&CLAY__MEASURED_WORD_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay__MeasuredWord *internalArray;
} Clay__MeasuredWordArray;
typedef struct
{
	uint32_t length;
	Clay__MeasuredWord *internalArray;
} Clay__MeasuredWordArraySlice;
Clay__MeasuredWordArray Clay__MeasuredWordArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__MeasuredWordArray){.capacity = capacity, .length = 0, .internalArray = (Clay__MeasuredWord *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay__MeasuredWord), CLAY__ALIGNMENT(Clay__MeasuredWord), arena)};
}
Clay__MeasuredWord *Clay__MeasuredWordArray_Get(Clay__MeasuredWordArray *array, int index) {
    return Clay__Array_RangeCheck(index, array->length) ? &array->internalArray[index] : &CLAY__MEASURED_WORD_DEFAULT;
}
Clay__MeasuredWord *Clay__MeasuredWordArraySlice_Get(Clay__MeasuredWordArraySlice *slice, int index) {
    return Clay__Array_RangeCheck(index, slice->length) ? &slice->internalArray[index] : &CLAY__MEASURED_WORD_DEFAULT;
}
Clay__MeasuredWord *Clay__MeasuredWordArray_Add(Clay__MeasuredWordArray *array, Clay__MeasuredWord item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__MEASURED_WORD_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

typedef struct
{
    Clay_Dimensions unwrappedDimensions;
    Clay__MeasuredWordArraySlice measuredWords;
    // Hash map data
    uint32_t id;
    int32_t nextIndex;
    uint32_t generation;
} Clay__MeasureTextCacheItem;

Clay__MeasureTextCacheItem CLAY__MEASURE_TEXT_CACHE_ITEM_DEFAULT = CLAY__INIT(Clay__MeasureTextCacheItem) { };

// __GENERATED__ template array_define,array_allocate,array_get,array_add,array_set TYPE=Clay__MeasureTextCacheItem NAME=Clay__MeasureTextCacheItemArray DEFAULT_VALUE=&CLAY__MEASURE_TEXT_CACHE_ITEM_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay__MeasureTextCacheItem *internalArray;
} Clay__MeasureTextCacheItemArray;
Clay__MeasureTextCacheItemArray Clay__MeasureTextCacheItemArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__MeasureTextCacheItemArray){.capacity = capacity, .length = 0, .internalArray = (Clay__MeasureTextCacheItem *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay__MeasureTextCacheItem), CLAY__ALIGNMENT(Clay__MeasureTextCacheItem), arena)};
}
Clay__MeasureTextCacheItem *Clay__MeasureTextCacheItemArray_Get(Clay__MeasureTextCacheItemArray *array, int index) {
    return Clay__Array_RangeCheck(index, array->length) ? &array->internalArray[index] : &CLAY__MEASURE_TEXT_CACHE_ITEM_DEFAULT;
}
Clay__MeasureTextCacheItem *Clay__MeasureTextCacheItemArray_Add(Clay__MeasureTextCacheItemArray *array, Clay__MeasureTextCacheItem item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__MEASURE_TEXT_CACHE_ITEM_DEFAULT;
}
void Clay__MeasureTextCacheItemArray_Set(Clay__MeasureTextCacheItemArray *array, int index, Clay__MeasureTextCacheItem value) {
	if (index < array->capacity && index >= 0) {
		array->internalArray[index] = value;
		array->length = index < array->length ? array->length : index + 1;
	} else {
	    if (Clay__warningsEnabled) {
            Clay__WarningArray_Add(&Clay_warnings, CLAY__INIT(Clay__Warning) { CLAY_STRING("Attempting to allocate array in arena, but arena is already at capacity and would overflow.") });
	    }
        #ifdef CLAY_OVERFLOW_TRAP
        raise(SIGTRAP);
        #endif
	}
}
#pragma endregion
// __GENERATED__ template

// __GENERATED__ template array_define,array_allocate,array_get_value,array_add_value,array_set,array_remove_swapback TYPE=int32_t NAME=Clay__int32_tArray DEFAULT_VALUE=-1
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	int32_t *internalArray;
} Clay__int32_tArray;
Clay__int32_tArray Clay__int32_tArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__int32_tArray){.capacity = capacity, .length = 0, .internalArray = (int32_t *)Clay__Array_Allocate_Arena(capacity, sizeof(int32_t), CLAY__ALIGNMENT(int32_t), arena)};
}
int32_t Clay__int32_tArray_Get(Clay__int32_tArray *array, int index) {
    return Clay__Array_RangeCheck(index, array->length) ? array->internalArray[index] : -1;
}
void Clay__int32_tArray_Add(Clay__int32_tArray *array, int32_t item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
	}
}
void Clay__int32_tArray_Set(Clay__int32_tArray *array, int index, int32_t value) {
	if (index < array->capacity && index >= 0) {
		array->internalArray[index] = value;
		array->length = index < array->length ? array->length : index + 1;
	} else {
	    if (Clay__warningsEnabled) {
            Clay__WarningArray_Add(&Clay_warnings, CLAY__INIT(Clay__Warning) { CLAY_STRING("Attempting to allocate array in arena, but arena is already at capacity and would overflow.") });
	    }
        #ifdef CLAY_OVERFLOW_TRAP
        raise(SIGTRAP);
        #endif
	}
}
int32_t Clay__int32_tArray_RemoveSwapback(Clay__int32_tArray *array, int index) {
	if (Clay__Array_RangeCheck(index, array->length)) {
		array->length--;
		int32_t removed = array->internalArray[index];
		array->internalArray[index] = array->internalArray[array->length];
		return removed;
	}
	return -1;
}
#pragma endregion
// __GENERATED__ template

typedef struct
{
    Clay_LayoutElement *layoutElement;
    Clay_Vector2 position;
    Clay_Vector2 nextChildOffset;
} Clay__LayoutElementTreeNode;

Clay__LayoutElementTreeNode CLAY__LAYOUT_ELEMENT_TREE_NODE_DEFAULT = CLAY__INIT(Clay__LayoutElementTreeNode) {};

// __GENERATED__ template array_define,array_allocate,array_add,array_get TYPE=Clay__LayoutElementTreeNode NAME=Clay__LayoutElementTreeNodeArray DEFAULT_VALUE=&CLAY__LAYOUT_ELEMENT_TREE_NODE_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay__LayoutElementTreeNode *internalArray;
} Clay__LayoutElementTreeNodeArray;
Clay__LayoutElementTreeNodeArray Clay__LayoutElementTreeNodeArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__LayoutElementTreeNodeArray){.capacity = capacity, .length = 0, .internalArray = (Clay__LayoutElementTreeNode *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay__LayoutElementTreeNode), CLAY__ALIGNMENT(Clay__LayoutElementTreeNode), arena)};
}
Clay__LayoutElementTreeNode *Clay__LayoutElementTreeNodeArray_Add(Clay__LayoutElementTreeNodeArray *array, Clay__LayoutElementTreeNode item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__LAYOUT_ELEMENT_TREE_NODE_DEFAULT;
}
Clay__LayoutElementTreeNode *Clay__LayoutElementTreeNodeArray_Get(Clay__LayoutElementTreeNodeArray *array, int index) {
    return Clay__Array_RangeCheck(index, array->length) ? &array->internalArray[index] : &CLAY__LAYOUT_ELEMENT_TREE_NODE_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

typedef struct
{
    uint32_t layoutElementIndex;
    uint32_t parentId; // This can be zero in the case of the root layout tree
    uint32_t clipElementId; // This can be zero if there is no clip element
    uint32_t zIndex;
} Clay__LayoutElementTreeRoot;

Clay__LayoutElementTreeRoot CLAY__LAYOUT_ELEMENT_TREE_ROOT_DEFAULT = CLAY__INIT(Clay__LayoutElementTreeRoot) {};

// __GENERATED__ template array_define,array_allocate,array_add,array_get TYPE=Clay__LayoutElementTreeRoot NAME=Clay__LayoutElementTreeRootArray DEFAULT_VALUE=&CLAY__LAYOUT_ELEMENT_TREE_ROOT_DEFAULT
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	Clay__LayoutElementTreeRoot *internalArray;
} Clay__LayoutElementTreeRootArray;
Clay__LayoutElementTreeRootArray Clay__LayoutElementTreeRootArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__LayoutElementTreeRootArray){.capacity = capacity, .length = 0, .internalArray = (Clay__LayoutElementTreeRoot *)Clay__Array_Allocate_Arena(capacity, sizeof(Clay__LayoutElementTreeRoot), CLAY__ALIGNMENT(Clay__LayoutElementTreeRoot), arena)};
}
Clay__LayoutElementTreeRoot *Clay__LayoutElementTreeRootArray_Add(Clay__LayoutElementTreeRootArray *array, Clay__LayoutElementTreeRoot item) {
	if (Clay__Array_IncrementCapacityCheck(array->length, array->capacity)) {
		array->internalArray[array->length++] = item;
		return &array->internalArray[array->length - 1];
	}
	return &CLAY__LAYOUT_ELEMENT_TREE_ROOT_DEFAULT;
}
Clay__LayoutElementTreeRoot *Clay__LayoutElementTreeRootArray_Get(Clay__LayoutElementTreeRootArray *array, int index) {
    return Clay__Array_RangeCheck(index, array->length) ? &array->internalArray[index] : &CLAY__LAYOUT_ELEMENT_TREE_ROOT_DEFAULT;
}
#pragma endregion
// __GENERATED__ template

// __GENERATED__ template array_define,array_allocate TYPE=uint8_t NAME=Clay__CharArray DEFAULT_VALUE=0
#pragma region generated
typedef struct
{
	uint32_t capacity;
	uint32_t length;
	uint8_t *internalArray;
} Clay__CharArray;
Clay__CharArray Clay__CharArray_Allocate_Arena(uint32_t capacity, Clay_Arena *arena) {
    return CLAY__INIT(Clay__CharArray){.capacity = capacity, .length = 0, .internalArray = (uint8_t *)Clay__Array_Allocate_Arena(capacity, sizeof(uint8_t), CLAY__ALIGNMENT(uint8_t), arena)};
}
#pragma endregion
// __GENERATED__ template

Clay_String Clay__WriteStringToCharBuffer(Clay__CharArray *buffer, Clay_String string) {
    for (int i = 0; i < string.length; i++) {
        buffer->internalArray[buffer->length + i] = string.chars[i];
    }
    buffer->length += string.length;
    return CLAY__INIT(Clay_String) { .length = string.length, .chars = (const char *)(buffer->internalArray + buffer->length - string.length) };
}

Clay_PointerData Clay__pointerInfo = CLAY__INIT(Clay_PointerData) { .position = {-1, -1} };
Clay_Dimensions Clay__layoutDimensions = CLAY__INIT(Clay_Dimensions){};
Clay_ElementId Clay__dynamicElementIndexBaseHash = CLAY__INIT(Clay_ElementId) { .id = 128476991, .stringId = { .length = 8, .chars = "Auto ID" } };
uint32_t Clay__dynamicElementIndex = 0;
bool Clay__debugModeEnabled = false;
uint32_t Clay__debugSelectedElementId = 0;
uint32_t Clay__debugViewWidth = 400;
Clay_Color Clay__debugViewHighlightColor = CLAY__INIT(Clay_Color) { 168, 66, 28, 100 };
uint32_t Clay__generation = 0;
uint64_t Clay__arenaResetOffset = 0;
Clay_Arena Clay__internalArena;
// Layout Elements / Render Commands
Clay_LayoutElementArray Clay__layoutElements;
Clay_RenderCommandArray Clay__renderCommands;
Clay__int32_tArray Clay__openLayoutElementStack;
Clay__int32_tArray Clay__layoutElementChildren;
Clay__int32_tArray Clay__layoutElementChildrenBuffer;
Clay__TextElementDataArray Clay__textElementData;
Clay__LayoutElementPointerArray Clay__imageElementPointers;
Clay__int32_tArray Clay__reusableElementIndexBuffer;
// Configs
Clay__LayoutConfigArray Clay__layoutConfigs;
Clay__ElementConfigArray Clay__elementConfigBuffer;
Clay__ElementConfigArray Clay__elementConfigs;
Clay__RectangleElementConfigArray Clay__rectangleElementConfigs;
Clay__TextElementConfigArray Clay__textElementConfigs;
Clay__ImageElementConfigArray Clay__imageElementConfigs;
Clay__FloatingElementConfigArray Clay__floatingElementConfigs;
Clay__ScrollElementConfigArray Clay__scrollElementConfigs;
Clay__CustomElementConfigArray Clay__customElementConfigs;
Clay__BorderElementConfigArray Clay__borderElementConfigs;
// Misc Data Structures
Clay__StringArray Clay__layoutElementIdStrings;
Clay__StringArray Clay__wrappedTextLines;
Clay__LayoutElementTreeNodeArray Clay__layoutElementTreeNodeArray1;
Clay__LayoutElementTreeRootArray Clay__layoutElementTreeRoots;
Clay__LayoutElementHashMapItemArray Clay__layoutElementsHashMapInternal;
Clay__int32_tArray Clay__layoutElementsHashMap;
Clay__MeasureTextCacheItemArray Clay__measureTextHashMapInternal;
Clay__int32_tArray Clay__measureTextHashMapInternalFreeList;
Clay__int32_tArray Clay__measureTextHashMap;
Clay__MeasuredWordArray Clay__measuredWords;
Clay__int32_tArray Clay__openClipElementStack;
Clay__ElementIdArray Clay__pointerOverIds;
Clay__ScrollContainerDataInternalArray Clay__scrollContainerDatas;
Clay__BoolArray Clay__treeNodeVisited;
Clay__CharArray Clay__dynamicStringData;
Clay__DebugElementDataArray Clay__debugElementData;

#if CLAY_WASM
    __attribute__((import_module("clay"), import_name("measureTextFunction"))) Clay_Dimensions Clay__MeasureText(Clay_String *text, Clay_TextElementConfig *config);
#else
    Clay_Dimensions (*Clay__MeasureText)(Clay_String *text, Clay_TextElementConfig *config);
#endif

Clay_LayoutElement* Clay__GetOpenLayoutElement() {
    return Clay_LayoutElementArray_Get(&Clay__layoutElements, Clay__int32_tArray_Get(&Clay__openLayoutElementStack, Clay__openLayoutElementStack.length - 1));
}

uint32_t Clay__GetParentElementId(void) {
    return Clay_LayoutElementArray_Get(&Clay__layoutElements, Clay__int32_tArray_Get(&Clay__openLayoutElementStack, Clay__openLayoutElementStack.length - 2))->id;
}

bool Clay__ElementHasConfig(Clay_LayoutElement *element, Clay__ElementConfigType type) {
    return (element->configsEnabled & type);
}

Clay_ElementConfigUnion Clay__FindElementConfigWithType(Clay_LayoutElement *element, Clay__ElementConfigType type) {
    for (int i = 0; i < element->elementConfigs.length; i++) {
        Clay_ElementConfig *config = Clay__ElementConfigArraySlice_Get(&element->elementConfigs, i);
        if (config->type == type) {
            return config->config;
        }
    }
    return CLAY__INIT(Clay_ElementConfigUnion) { NULL };
}

Clay_ElementId Clay__HashNumber(const uint32_t offset, const uint32_t seed) {
    uint32_t hash = seed;
    hash += (offset + 48);
    hash += (hash << 10);
    hash ^= (hash >> 6);

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return CLAY__INIT(Clay_ElementId) { .id = hash + 1, .offset = offset, .baseId = seed, .stringId = CLAY__STRING_DEFAULT }; // Reserve the hash result of zero as "null id"
}

Clay_ElementId Clay__HashString(Clay_String key, const uint32_t offset, const uint32_t seed) {
    uint32_t hash = 0;
    uint32_t base = seed;

    for (int i = 0; i < key.length; i++) {
        base += key.chars[i];
        base += (base << 10);
        base ^= (base >> 6);
    }
    hash = base;
    hash += offset;
    hash += (hash << 10);
    hash ^= (hash >> 6);

    hash += (hash << 3);
    base += (base << 3);
    hash ^= (hash >> 11);
    base ^= (base >> 11);
    hash += (hash << 15);
    base += (base << 15);
    return CLAY__INIT(Clay_ElementId) { .id = hash + 1, .offset = offset, .baseId = base + 1, .stringId = key }; // Reserve the hash result of zero as "null id"
}

Clay_ElementId Clay__Rehash(Clay_ElementId elementId, uint32_t number) {
    uint32_t id = elementId.baseId;
    id += number;
    id += (id << 10);
    id ^= (id >> 6);

    id += (id << 3);
    id ^= (id >> 11);
    id += (id << 15);
    return CLAY__INIT(Clay_ElementId) { .id = id, .offset = number, .baseId = elementId.baseId, .stringId = elementId.stringId };
}

uint32_t Clay__RehashWithNumber(uint32_t id, uint32_t number) {
    id += number;
    id += (id << 10);
    id ^= (id >> 6);

    id += (id << 3);
    id ^= (id >> 11);
    id += (id << 15);
    return id;
}

uint32_t Clay__HashTextWithConfig(Clay_String *text, Clay_TextElementConfig *config) {
    uint32_t hash = 0;
    uint64_t pointerAsNumber = (uint64_t)text->chars;

    hash += pointerAsNumber;
    hash += (hash << 10);
    hash ^= (hash >> 6);

    hash += text->length;
    hash += (hash << 10);
    hash ^= (hash >> 6);

    uint64_t configPointerAsNumber = (uint64_t)config;
    hash += configPointerAsNumber;
    hash += (hash << 10);
    hash ^= (hash >> 6);

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash + 1; // Reserve the hash result of zero as "null id"
}

Clay__MeasureTextCacheItem *Clay__MeasureTextCached(Clay_String *text, Clay_TextElementConfig *config) {
    uint32_t id = Clay__HashTextWithConfig(text, config);
    uint32_t hashBucket = id % Clay__measureTextHashMap.capacity;
    int32_t elementIndexPrevious = 0;
    int32_t elementIndex = Clay__measureTextHashMap.internalArray[hashBucket];
    while (elementIndex != 0) {
        Clay__MeasureTextCacheItem *hashEntry = Clay__MeasureTextCacheItemArray_Get(&Clay__measureTextHashMapInternal, elementIndex);
        if (hashEntry->id == id) {
            hashEntry->generation = Clay__generation;
            return hashEntry;
        }
        // This element hasn't been seen in a few frames, delete the hash map item
        if (Clay__generation - hashEntry->generation > 2) {
            uint32_t nextIndex = hashEntry->nextIndex;
            Clay__MeasureTextCacheItemArray_Set(&Clay__measureTextHashMapInternal, elementIndex, CLAY__INIT(Clay__MeasureTextCacheItem) {});
            Clay__int32_tArray_Add(&Clay__measureTextHashMapInternalFreeList, elementIndex);
            if (elementIndexPrevious == 0) {
                Clay__measureTextHashMap.internalArray[hashBucket] = nextIndex;
            } else {
                Clay__MeasureTextCacheItem *previousHashEntry = Clay__MeasureTextCacheItemArray_Get(&Clay__measureTextHashMapInternal, elementIndexPrevious);
                previousHashEntry->nextIndex = nextIndex;
            }
            elementIndex = nextIndex;
        } else {
            elementIndexPrevious = elementIndex;
            elementIndex = hashEntry->nextIndex;
        }
    }

    uint32_t newItemIndex = 0;
    Clay__MeasureTextCacheItem newCacheItem = CLAY__INIT(Clay__MeasureTextCacheItem) { .measuredWords = CLAY__INIT(Clay__MeasuredWordArraySlice) { .length = 0, .internalArray = &Clay__measuredWords.internalArray[Clay__measuredWords.length] }, .id = id, .generation = Clay__generation };
    Clay__MeasureTextCacheItem *measured = NULL;
    if (Clay__measureTextHashMapInternalFreeList.length > 0) {
        newItemIndex = Clay__int32_tArray_Get(&Clay__measureTextHashMapInternalFreeList, Clay__measureTextHashMapInternalFreeList.length - 1);
        Clay__measureTextHashMapInternalFreeList.length--;
        Clay__MeasureTextCacheItemArray_Set(&Clay__measureTextHashMapInternal, newItemIndex, newCacheItem);
        measured = Clay__MeasureTextCacheItemArray_Get(&Clay__measureTextHashMapInternal, newItemIndex);
    } else {
        if (Clay__measureTextHashMapInternal.length == Clay__measureTextHashMapInternal.capacity) {
            return NULL;
        }
        measured = Clay__MeasureTextCacheItemArray_Add(&Clay__measureTextHashMapInternal, newCacheItem);
        newItemIndex = Clay__measureTextHashMapInternal.length - 1;
    }

    uint32_t start = 0;
    uint32_t end = 0;
    float measuredWidth = 0;
    float measuredHeight = 0;
    float spaceWidth = Clay__MeasureText(&CLAY__SPACECHAR, config).width;
    while (end < text->length) {
        char current = text->chars[end];
        if (current == ' ' || current == '\n') {
            uint32_t length = end - start;
            Clay_String word = CLAY__INIT(Clay_String) { .length = (int)length, .chars = &text->chars[start] };
            Clay_Dimensions dimensions = Clay__MeasureText(&word, config);
            if (current == ' ') {
                dimensions.width += spaceWidth;
                Clay__MeasuredWordArray_Add(&Clay__measuredWords, CLAY__INIT(Clay__MeasuredWord) { .word = word, .startOffset = start, .length = length + 1, .width = dimensions.width });
            }
            if (current == '\n') {
                Clay__MeasuredWordArray_Add(&Clay__measuredWords, CLAY__INIT(Clay__MeasuredWord) { .word = word, .startOffset = start, .length = length, .width = dimensions.width });
                Clay__MeasuredWordArray_Add(&Clay__measuredWords, CLAY__INIT(Clay__MeasuredWord) { .word = CLAY__INIT(Clay_String) { .length = 0, .chars = &text->chars[end] }, .startOffset = end + 1, .length = 0, .width = 0 });
                measured->measuredWords.length++;
            }
            measuredWidth += dimensions.width;
            measuredHeight = dimensions.height;
            measured->measuredWords.length++;
            start = end + 1;
        }
        end++;
    }
    if (end - start > 0) {
        Clay_String lastWord = CLAY__INIT(Clay_String) { .length = (int)(end - start), .chars = &text->chars[start] };
        Clay_Dimensions dimensions = Clay__MeasureText(&lastWord, config);
        Clay__MeasuredWordArray_Add(&Clay__measuredWords, CLAY__INIT(Clay__MeasuredWord) { .word = lastWord, .startOffset = start, .length = end - start, .width = dimensions.width });
        measuredWidth += dimensions.width;
        measuredHeight = dimensions.height;
        measured->measuredWords.length++;
    }
    measured->unwrappedDimensions.width = measuredWidth;
    measured->unwrappedDimensions.height = measuredHeight;

    if (elementIndexPrevious != 0) {
        Clay__MeasureTextCacheItemArray_Get(&Clay__measureTextHashMapInternal, elementIndexPrevious)->nextIndex = newItemIndex;
    } else {
        Clay__measureTextHashMap.internalArray[hashBucket] = newItemIndex;
    }
    return measured;
}

bool Clay__PointIsInsideRect(Clay_Vector2 point, Clay_BoundingBox rect) {
    return point.x >= rect.x && point.x <= rect.x + rect.width && point.y >= rect.y && point.y <= rect.y + rect.height;
}

Clay_LayoutElementHashMapItem* Clay__AddHashMapItem(Clay_ElementId elementId, Clay_LayoutElement* layoutElement) {
    Clay_LayoutElementHashMapItem item = CLAY__INIT(Clay_LayoutElementHashMapItem) { .elementId = elementId, .layoutElement = layoutElement, .nextIndex = -1, .generation = Clay__generation + 1 };
    uint32_t hashBucket = elementId.id % Clay__layoutElementsHashMap.capacity;
    int32_t hashItemPrevious = -1;
    int32_t hashItemIndex = Clay__layoutElementsHashMap.internalArray[hashBucket];
    while (hashItemIndex != -1) { // Just replace collision, not a big deal - leave it up to the end user
        Clay_LayoutElementHashMapItem *hashItem = Clay__LayoutElementHashMapItemArray_Get(&Clay__layoutElementsHashMapInternal, hashItemIndex);
        if (hashItem->elementId.id == elementId.id) { // Collision - resolve based on generation
            item.nextIndex = hashItem->nextIndex;
            if (hashItem->generation <= Clay__generation) { // First collision - assume this is the "same" element
                hashItem->generation = Clay__generation + 1;
                hashItem->layoutElement = layoutElement;
                hashItem->debugData->collision = false;
            } else { // Multiple collisions this frame - two elements have the same ID
                if (Clay__warningsEnabled) {
                    Clay__WarningArray_Add(&Clay_warnings, CLAY__INIT(Clay__Warning) { CLAY_STRING("Duplicate ID detected for element: "), Clay__WriteStringToCharBuffer(&Clay__dynamicStringData, elementId.stringId) });
                }
                if (Clay__debugModeEnabled) {
                    hashItem->debugData->collision = true;
                }
            }
            return hashItem;
        }
        hashItemPrevious = hashItemIndex;
        hashItemIndex = hashItem->nextIndex;
    }
    Clay_LayoutElementHashMapItem *hashItem = Clay__LayoutElementHashMapItemArray_Add(&Clay__layoutElementsHashMapInternal, item);
    hashItem->debugData = Clay__DebugElementDataArray_Add(&Clay__debugElementData, CLAY__INIT(Clay__DebugElementData) {});
    if (hashItemPrevious != -1) {
        Clay__LayoutElementHashMapItemArray_Get(&Clay__layoutElementsHashMapInternal, hashItemPrevious)->nextIndex = (int32_t)Clay__layoutElementsHashMapInternal.length - 1;
    } else {
        Clay__layoutElementsHashMap.internalArray[hashBucket] = (int32_t)Clay__layoutElementsHashMapInternal.length - 1;
    }
    return hashItem;
}

Clay_LayoutElementHashMapItem *Clay__GetHashMapItem(uint32_t id) {
    uint32_t hashBucket = id % Clay__layoutElementsHashMap.capacity;
    int32_t elementIndex = Clay__layoutElementsHashMap.internalArray[hashBucket];
    while (elementIndex != -1) {
        Clay_LayoutElementHashMapItem *hashEntry = Clay__LayoutElementHashMapItemArray_Get(&Clay__layoutElementsHashMapInternal, elementIndex);
        if (hashEntry->elementId.id == id) {
            return hashEntry;
        }
        elementIndex = hashEntry->nextIndex;
    }
    return CLAY__NULL;
}

void Clay__GenerateIdForAnonymousElement(Clay_LayoutElement *openLayoutElement) {
    Clay_LayoutElement *parentElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, Clay__int32_tArray_Get(&Clay__openLayoutElementStack, Clay__openLayoutElementStack.length - 2));
    Clay_ElementId elementId = Clay__HashNumber(parentElement->children.length, parentElement->id);
    openLayoutElement->id = elementId.id;
    Clay__AddHashMapItem(elementId, openLayoutElement);
    Clay__StringArray_Add(&Clay__layoutElementIdStrings, elementId.stringId);
    #ifdef CLAY_DEBUG
    openLayoutElement->name = elementId.stringId;
    #endif
}

void Clay__ElementPostConfiguration() {
    Clay_LayoutElement *openLayoutElement = Clay__GetOpenLayoutElement();
    // ID
    if (openLayoutElement->id == 0) {
        Clay__GenerateIdForAnonymousElement(openLayoutElement);
    }
    // Layout Config
    if (!openLayoutElement->layoutConfig) {
        openLayoutElement->layoutConfig = &CLAY_LAYOUT_DEFAULT;
    }

    // Loop through element configs and handle special cases
    openLayoutElement->elementConfigs.internalArray = &Clay__elementConfigs.internalArray[Clay__elementConfigs.length];
    for (int elementConfigIndex = 0; elementConfigIndex < openLayoutElement->elementConfigs.length; elementConfigIndex++) {
        Clay_ElementConfig *config = Clay__ElementConfigArray_Add(&Clay__elementConfigs, *Clay__ElementConfigArray_Get(&Clay__elementConfigBuffer, Clay__elementConfigBuffer.length - openLayoutElement->elementConfigs.length + elementConfigIndex));
        openLayoutElement->configsEnabled |= config->type;
        switch (config->type) {
            case CLAY__ELEMENT_CONFIG_TYPE_RECTANGLE: break;
            case CLAY__ELEMENT_CONFIG_TYPE_BORDER_CONTAINER: break;
            case CLAY__ELEMENT_CONFIG_TYPE_FLOATING_CONTAINER: {
                Clay_FloatingElementConfig *floatingConfig = config->config.floatingElementConfig;
                // This looks dodgy but because of the auto generated root element the depth of the tree will always be at least 2 here
                Clay_LayoutElement *hierarchicalParent = Clay_LayoutElementArray_Get(&Clay__layoutElements, Clay__int32_tArray_Get(&Clay__openLayoutElementStack, Clay__openLayoutElementStack.length - 2));
                if (!hierarchicalParent) {
                    break;
                }
                int clipElementId = 0;
                if (floatingConfig->parentId == 0) {
                    // If no parent id was specified, attach to the elements direct hierarchical parent
                    Clay_FloatingElementConfig newConfig = *floatingConfig;
                    newConfig.parentId = hierarchicalParent->id;
                    floatingConfig = Clay__FloatingElementConfigArray_Add(&Clay__floatingElementConfigs, newConfig);
                    config->config.floatingElementConfig = floatingConfig;
                    if (Clay__openClipElementStack.length > 0) {
                        clipElementId = Clay__int32_tArray_Get(&Clay__openClipElementStack, (int)Clay__openClipElementStack.length - 1);
                    }
                } else {
                    Clay_LayoutElementHashMapItem *parentItem = Clay__GetHashMapItem(floatingConfig->parentId);
                    if (!parentItem) {
                        Clay__WarningArray_Add(&Clay_warnings, CLAY__INIT(Clay__Warning) { CLAY_STRING("Clay Warning: Couldn't find parent container to attach floating container to.") });
                    }
                }
                Clay__LayoutElementTreeRootArray_Add(&Clay__layoutElementTreeRoots, CLAY__INIT(Clay__LayoutElementTreeRoot) {
                    .layoutElementIndex = (uint32_t)Clay__int32_tArray_Get(&Clay__openLayoutElementStack, Clay__openLayoutElementStack.length - 1),
                    .parentId = floatingConfig->parentId,
                    .clipElementId = (uint32_t)clipElementId,
                    .zIndex = floatingConfig->zIndex,
                });
                break;
            }
            case CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER: {
                Clay__int32_tArray_Add(&Clay__openClipElementStack, (int)openLayoutElement->id);
                // Retrieve or create cached data to track scroll position across frames
                Clay__ScrollContainerDataInternal *scrollOffset = CLAY__NULL;
                for (int i = 0; i < Clay__scrollContainerDatas.length; i++) {
                    Clay__ScrollContainerDataInternal *mapping = Clay__ScrollContainerDataInternalArray_Get(&Clay__scrollContainerDatas, i);
                    if (openLayoutElement->id == mapping->elementId) {
                        scrollOffset = mapping;
                        scrollOffset->layoutElement = openLayoutElement;
                        scrollOffset->openThisFrame = true;
                    }
                }
                if (!scrollOffset) {
                    Clay__ScrollContainerDataInternalArray_Add(&Clay__scrollContainerDatas, CLAY__INIT(Clay__ScrollContainerDataInternal){.layoutElement = openLayoutElement, .scrollOrigin = {-1,-1}, .elementId = openLayoutElement->id, .openThisFrame = true});
                }
                break;
            }
            case CLAY__ELEMENT_CONFIG_TYPE_CUSTOM: break;
            case CLAY__ELEMENT_CONFIG_TYPE_IMAGE: {
                Clay__LayoutElementPointerArray_Add(&Clay__imageElementPointers, openLayoutElement);
                break;
            }
            case CLAY__ELEMENT_CONFIG_TYPE_TEXT: break;
        }
    }
    Clay__elementConfigBuffer.length -= openLayoutElement->elementConfigs.length;
}

void Clay__CloseElement() {
    Clay_LayoutElement *openLayoutElement = Clay__GetOpenLayoutElement();
    Clay_LayoutConfig *layoutConfig = openLayoutElement->layoutConfig;
    bool elementHasScrollHorizontal = false;
    bool elementHasScrollVertical = false;
    if (Clay__ElementHasConfig(openLayoutElement, CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER)) {
        Clay_ScrollElementConfig *scrollConfig = Clay__FindElementConfigWithType(openLayoutElement, CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER).scrollElementConfig;
        elementHasScrollHorizontal = scrollConfig->horizontal;
        elementHasScrollVertical = scrollConfig->vertical;
        Clay__openClipElementStack.length--;
    }

    // Attach children to the current open element
    openLayoutElement->children.elements = &Clay__layoutElementChildren.internalArray[Clay__layoutElementChildren.length];
    if (layoutConfig->layoutDirection == CLAY_LEFT_TO_RIGHT) {
        openLayoutElement->dimensions.width = layoutConfig->padding.x * 2;
        for (int i = 0; i < openLayoutElement->children.length; i++) {
            int32_t childIndex = Clay__int32_tArray_Get(&Clay__layoutElementChildrenBuffer, (int)Clay__layoutElementChildrenBuffer.length - openLayoutElement->children.length + i);
            Clay_LayoutElement *child = Clay_LayoutElementArray_Get(&Clay__layoutElements, childIndex);
            openLayoutElement->dimensions.width += child->dimensions.width;
            openLayoutElement->dimensions.height = CLAY__MAX(openLayoutElement->dimensions.height, child->dimensions.height + layoutConfig->padding.y * 2);
            // Minimum size of child elements doesn't matter to scroll containers as they can shrink and hide their contents
            if (!elementHasScrollHorizontal) {
                openLayoutElement->minDimensions.width += child->minDimensions.width;
            }
            if (!elementHasScrollVertical) {
                openLayoutElement->minDimensions.height = CLAY__MAX(openLayoutElement->minDimensions.height, child->minDimensions.height + layoutConfig->padding.y * 2);
            }
            Clay__int32_tArray_Add(&Clay__layoutElementChildren, childIndex);
        }
        float childGap = (float)(CLAY__MAX(openLayoutElement->children.length - 1, 0) * layoutConfig->childGap);
        openLayoutElement->dimensions.width += childGap; // TODO this is technically a bug with childgap and scroll containers
        openLayoutElement->minDimensions.width += childGap;
    }
    else if (layoutConfig->layoutDirection == CLAY_TOP_TO_BOTTOM) {
        openLayoutElement->dimensions.height = layoutConfig->padding.y * 2;
        for (int i = 0; i < openLayoutElement->children.length; i++) {
            int32_t childIndex = Clay__int32_tArray_Get(&Clay__layoutElementChildrenBuffer, (int)Clay__layoutElementChildrenBuffer.length - openLayoutElement->children.length + i);
            Clay_LayoutElement *child = Clay_LayoutElementArray_Get(&Clay__layoutElements, childIndex);
            openLayoutElement->dimensions.height += child->dimensions.height;
            openLayoutElement->dimensions.width = CLAY__MAX(openLayoutElement->dimensions.width, child->dimensions.width + layoutConfig->padding.x * 2);
            // Minimum size of child elements doesn't matter to scroll containers as they can shrink and hide their contents
            if (!elementHasScrollVertical) {
                openLayoutElement->minDimensions.height += child->minDimensions.height;
            }
            if (!elementHasScrollHorizontal) {
                openLayoutElement->minDimensions.width = CLAY__MAX(openLayoutElement->minDimensions.width, child->minDimensions.width + layoutConfig->padding.x * 2);
            }
            Clay__int32_tArray_Add(&Clay__layoutElementChildren, childIndex);
        }
        float childGap = (float)(CLAY__MAX(openLayoutElement->children.length - 1, 0) * layoutConfig->childGap);
        openLayoutElement->dimensions.height += childGap; // TODO this is technically a bug with childgap and scroll containers
        openLayoutElement->minDimensions.height += childGap;
    }

    Clay__layoutElementChildrenBuffer.length -= openLayoutElement->children.length;

    // Clamp element min and max width to the values configured in the layout
    if (layoutConfig->sizing.width.type != CLAY__SIZING_TYPE_PERCENT) {
        if (layoutConfig->sizing.width.sizeMinMax.max <= 0) { // Set the max size if the user didn't specify, makes calculations easier
            layoutConfig->sizing.width.sizeMinMax.max = CLAY__MAXFLOAT;
        }
        openLayoutElement->dimensions.width = CLAY__MIN(CLAY__MAX(openLayoutElement->dimensions.width, layoutConfig->sizing.width.sizeMinMax.min), layoutConfig->sizing.width.sizeMinMax.max);
        openLayoutElement->minDimensions.width = CLAY__MIN(CLAY__MAX(openLayoutElement->minDimensions.width, layoutConfig->sizing.width.sizeMinMax.min), layoutConfig->sizing.width.sizeMinMax.max);
    } else {
        openLayoutElement->dimensions.width = 0;
    }

    // Clamp element min and max height to the values configured in the layout
    if (layoutConfig->sizing.height.type != CLAY__SIZING_TYPE_PERCENT) {
        if (layoutConfig->sizing.height.sizeMinMax.max <= 0) { // Set the max size if the user didn't specify, makes calculations easier
            layoutConfig->sizing.height.sizeMinMax.max = CLAY__MAXFLOAT;
        }
        openLayoutElement->dimensions.height = CLAY__MIN(CLAY__MAX(openLayoutElement->dimensions.height, layoutConfig->sizing.height.sizeMinMax.min), layoutConfig->sizing.height.sizeMinMax.max);
        openLayoutElement->minDimensions.height = CLAY__MIN(CLAY__MAX(openLayoutElement->minDimensions.height, layoutConfig->sizing.height.sizeMinMax.min), layoutConfig->sizing.height.sizeMinMax.max);
    } else {
        openLayoutElement->dimensions.height = 0;
    }

    bool elementIsFloating = Clay__ElementHasConfig(openLayoutElement, CLAY__ELEMENT_CONFIG_TYPE_FLOATING_CONTAINER);

    // Close the currently open element
    int32_t closingElementIndex = Clay__int32_tArray_RemoveSwapback(&Clay__openLayoutElementStack, (int)Clay__openLayoutElementStack.length - 1);
    openLayoutElement = Clay__GetOpenLayoutElement();

    if (!elementIsFloating && Clay__openLayoutElementStack.length > 1) {
        openLayoutElement->children.length++;
        Clay__int32_tArray_Add(&Clay__layoutElementChildrenBuffer, closingElementIndex);
    }
}

void Clay__OpenElement() {
    Clay_LayoutElement layoutElement = CLAY__INIT(Clay_LayoutElement) {};
    Clay_LayoutElementArray_Add(&Clay__layoutElements, layoutElement);
    Clay__int32_tArray_Add(&Clay__openLayoutElementStack, Clay__layoutElements.length - 1);
}

void Clay__OpenTextElement(Clay_String text, Clay_TextElementConfig *textConfig) {
    Clay_LayoutElement *parentElement = Clay__GetOpenLayoutElement();
    parentElement->children.length++;

    Clay__OpenElement();
    Clay_LayoutElement * openLayoutElement = Clay__GetOpenLayoutElement();
    Clay__int32_tArray_Add(&Clay__layoutElementChildrenBuffer, Clay__layoutElements.length - 1);
    Clay__MeasureTextCacheItem *textMeasured = Clay__MeasureTextCached(&text, textConfig);
    Clay_ElementId elementId = Clay__HashString(CLAY_STRING("Text"), parentElement->children.length, parentElement->id);
    openLayoutElement->id = elementId.id;
    #ifdef CLAY_DEBUG
        openLayoutElement->name = CLAY_STRING("Text");
    #endif
    Clay__AddHashMapItem(elementId, openLayoutElement);
    Clay__StringArray_Add(&Clay__layoutElementIdStrings, elementId.stringId);
    Clay_Dimensions textDimensions = CLAY__INIT(Clay_Dimensions) { .width = textMeasured->unwrappedDimensions.width, .height = textConfig->lineHeight > 0 ? textConfig->lineHeight : textMeasured->unwrappedDimensions.height };
    openLayoutElement->dimensions = textDimensions;
    openLayoutElement->minDimensions = CLAY__INIT(Clay_Dimensions) { .width = textMeasured->unwrappedDimensions.height, .height = textDimensions.height }; // TODO not sure this is the best way to decide min width for text
    openLayoutElement->textElementData = Clay__TextElementDataArray_Add(&Clay__textElementData, CLAY__INIT(Clay__TextElementData) { .text = text, .preferredDimensions = textMeasured->unwrappedDimensions, .elementIndex = Clay__layoutElements.length - 1 });
    openLayoutElement->elementConfigs = CLAY__INIT(Clay__ElementConfigArraySlice) {
        .length = 1,
        .internalArray = Clay__ElementConfigArray_Add(&Clay__elementConfigs, CLAY__INIT(Clay_ElementConfig) { .type = CLAY__ELEMENT_CONFIG_TYPE_TEXT, .config = { .textElementConfig = textConfig }})
    };
    openLayoutElement->configsEnabled |= CLAY__ELEMENT_CONFIG_TYPE_TEXT;
    openLayoutElement->layoutConfig = &CLAY_LAYOUT_DEFAULT;
    // Close the currently open element
    Clay__int32_tArray_RemoveSwapback(&Clay__openLayoutElementStack, (int)Clay__openLayoutElementStack.length - 1);
}

void Clay__InitializeEphemeralMemory(Clay_Arena *arena) {
    // Ephemeral Memory - reset every frame
    Clay__internalArena.nextAllocation = Clay__arenaResetOffset;

    Clay__layoutElementChildrenBuffer = Clay__int32_tArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__layoutElements = Clay_LayoutElementArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay_warnings = Clay__WarningArray_Allocate_Arena(100, arena);

    Clay__layoutConfigs = Clay__LayoutConfigArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__elementConfigBuffer = Clay__ElementConfigArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__elementConfigs = Clay__ElementConfigArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__rectangleElementConfigs = Clay__RectangleElementConfigArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__textElementConfigs = Clay__TextElementConfigArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__imageElementConfigs = Clay__ImageElementConfigArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__floatingElementConfigs = Clay__FloatingElementConfigArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__scrollElementConfigs = Clay__ScrollElementConfigArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__customElementConfigs = Clay__CustomElementConfigArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__borderElementConfigs = Clay__BorderElementConfigArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);

    Clay__layoutElementIdStrings = Clay__StringArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__wrappedTextLines = Clay__StringArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__layoutElementTreeNodeArray1 = Clay__LayoutElementTreeNodeArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__layoutElementTreeRoots = Clay__LayoutElementTreeRootArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__layoutElementChildren = Clay__int32_tArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__openLayoutElementStack = Clay__int32_tArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__textElementData = Clay__TextElementDataArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__imageElementPointers = Clay__LayoutElementPointerArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__renderCommands = Clay_RenderCommandArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__treeNodeVisited = Clay__BoolArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__treeNodeVisited.length = Clay__treeNodeVisited.capacity; // This array is accessed directly rather than behaving as a list
    Clay__openClipElementStack = Clay__int32_tArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__reusableElementIndexBuffer = Clay__int32_tArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__dynamicStringData = Clay__CharArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
}

void Clay__InitializePersistentMemory(Clay_Arena *arena) {
    // Persistent memory - initialized once and not reset
    Clay__scrollContainerDatas = Clay__ScrollContainerDataInternalArray_Allocate_Arena(10, arena);
    Clay__layoutElementsHashMapInternal = Clay__LayoutElementHashMapItemArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__layoutElementsHashMap = Clay__int32_tArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__measureTextHashMapInternal = Clay__MeasureTextCacheItemArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__measureTextHashMapInternalFreeList = Clay__int32_tArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__measureTextHashMap = Clay__int32_tArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__measuredWords = Clay__MeasuredWordArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT * 2, arena);
    Clay__pointerOverIds = Clay__ElementIdArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__debugElementData = Clay__DebugElementDataArray_Allocate_Arena(CLAY_MAX_ELEMENT_COUNT, arena);
    Clay__arenaResetOffset = arena->nextAllocation;
}


typedef enum
{
    CLAY__SIZE_DISTRIBUTION_TYPE_SCROLL_CONTAINER,
    CLAY__SIZE_DISTRIBUTION_TYPE_RESIZEABLE_CONTAINER,
    CLAY__SIZE_DISTRIBUTION_TYPE_GROW_CONTAINER,
} Clay__SizeDistributionType;

float Clay__DistributeSizeAmongChildren(bool xAxis, float sizeToDistribute, Clay__int32_tArray resizableContainerBuffer, Clay__SizeDistributionType distributionType) {
    Clay__int32_tArray remainingElements = Clay__openClipElementStack;
    remainingElements.length = 0;

    for (int i = 0; i < resizableContainerBuffer.length; ++i) {
        Clay__int32_tArray_Add(&remainingElements, Clay__int32_tArray_Get(&resizableContainerBuffer, i));
    }

    while (sizeToDistribute != 0 && remainingElements.length > 0) {
        float dividedSize = sizeToDistribute / (float)remainingElements.length;
        for (int childOffset = 0; childOffset < remainingElements.length; childOffset++) {
            Clay_LayoutElement *childElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, Clay__int32_tArray_Get(&remainingElements, childOffset));
            Clay_SizingAxis childSizing = xAxis ? childElement->layoutConfig->sizing.width : childElement->layoutConfig->sizing.height;
            float *childSize = xAxis ? &childElement->dimensions.width : &childElement->dimensions.height;
            float childMinSize = xAxis ? childElement->minDimensions.width : childElement->minDimensions.height;
            bool canDistribute = true;

            if ((sizeToDistribute < 0 && *childSize == childSizing.sizeMinMax.min) || (sizeToDistribute > 0 && *childSize == childSizing.sizeMinMax.max)) {
                canDistribute = false;
            }
            // Currently, we don't support squishing aspect ratio images on their Y axis as it would break ratio
            else if (!xAxis && Clay__ElementHasConfig(childElement, CLAY__ELEMENT_CONFIG_TYPE_IMAGE)) {
                canDistribute = false;
            }
            else {
                switch (distributionType) {
                    case CLAY__SIZE_DISTRIBUTION_TYPE_RESIZEABLE_CONTAINER: break;
                    case CLAY__SIZE_DISTRIBUTION_TYPE_GROW_CONTAINER: if (childSizing.type != CLAY__SIZING_TYPE_GROW) canDistribute = false; break;
                    case CLAY__SIZE_DISTRIBUTION_TYPE_SCROLL_CONTAINER: {
                        if (Clay__ElementHasConfig(childElement, CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER)) {
                            Clay_ScrollElementConfig *scrollConfig = Clay__FindElementConfigWithType(childElement, CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER).scrollElementConfig;
                            if ((xAxis && !scrollConfig->horizontal) || (!xAxis && !scrollConfig->vertical)) {
                                Clay__int32_tArray_RemoveSwapback(&remainingElements, childOffset);
                                childOffset--;
                                continue;
                            }
                        }
                    }
                }
            }

            if (!canDistribute) {
                Clay__int32_tArray_RemoveSwapback(&remainingElements, childOffset);
                childOffset--;
                continue;
            }

            float oldChildSize = *childSize;
            *childSize = CLAY__MAX(CLAY__MAX(CLAY__MIN(childSizing.sizeMinMax.max, *childSize + dividedSize), childSizing.sizeMinMax.min), childMinSize);
            float diff = *childSize - oldChildSize;
            if (diff > -0.01 && diff < 0.01) {
                Clay__int32_tArray_RemoveSwapback(&remainingElements, childOffset);
                childOffset--;
                continue;
            }
            sizeToDistribute -= diff;
        }
    }
    return (sizeToDistribute > -0.01 && sizeToDistribute < 0.01) ? 0 : sizeToDistribute;
}

void Clay__SizeContainersAlongAxis(bool xAxis) {
    Clay__int32_tArray bfsBuffer = Clay__layoutElementChildrenBuffer;
    Clay__int32_tArray resizableContainerBuffer = Clay__openLayoutElementStack;
    for (int rootIndex = 0; rootIndex < Clay__layoutElementTreeRoots.length; ++rootIndex) {
        bfsBuffer.length = 0;
        Clay__LayoutElementTreeRoot *root = Clay__LayoutElementTreeRootArray_Get(&Clay__layoutElementTreeRoots, rootIndex);
        Clay_LayoutElement *rootElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, (int)root->layoutElementIndex);
        Clay__int32_tArray_Add(&bfsBuffer, (int32_t)root->layoutElementIndex);

        // Size floating containers to their parents
        if (Clay__ElementHasConfig(rootElement, CLAY__ELEMENT_CONFIG_TYPE_FLOATING_CONTAINER)) {
            Clay_FloatingElementConfig *floatingElementConfig = Clay__FindElementConfigWithType(rootElement, CLAY__ELEMENT_CONFIG_TYPE_FLOATING_CONTAINER).floatingElementConfig;
            Clay_LayoutElementHashMapItem *parentItem = Clay__GetHashMapItem(floatingElementConfig->parentId);
            if (parentItem) {
                Clay_LayoutElement *parentLayoutElement = parentItem->layoutElement;
                if (rootElement->layoutConfig->sizing.width.type == CLAY__SIZING_TYPE_GROW) {
                    rootElement->dimensions.width = parentLayoutElement->dimensions.width;
                }
                if (rootElement->layoutConfig->sizing.height.type == CLAY__SIZING_TYPE_GROW) {
                    rootElement->dimensions.height = parentLayoutElement->dimensions.height;
                }
            }
        }

        rootElement->dimensions.width = CLAY__MIN(CLAY__MAX(rootElement->dimensions.width, rootElement->layoutConfig->sizing.width.sizeMinMax.min), rootElement->layoutConfig->sizing.width.sizeMinMax.max);
        rootElement->dimensions.height = CLAY__MIN(CLAY__MAX(rootElement->dimensions.height, rootElement->layoutConfig->sizing.height.sizeMinMax.min), rootElement->layoutConfig->sizing.height.sizeMinMax.max);

        for (int i = 0; i < bfsBuffer.length; ++i) {
            int32_t parentIndex = Clay__int32_tArray_Get(&bfsBuffer, i);
            Clay_LayoutElement *parent = Clay_LayoutElementArray_Get(&Clay__layoutElements, parentIndex);
            Clay_LayoutConfig *parentStyleConfig = parent->layoutConfig;
            int growContainerCount = 0;
            float parentSize = xAxis ? parent->dimensions.width : parent->dimensions.height;
            float parentPadding = (float)(xAxis ? parent->layoutConfig->padding.x : parent->layoutConfig->padding.y);
            float innerContentSize = 0, growContainerContentSize = 0, totalPaddingAndChildGaps = parentPadding * 2;
            bool sizingAlongAxis = (xAxis && parentStyleConfig->layoutDirection == CLAY_LEFT_TO_RIGHT) || (!xAxis && parentStyleConfig->layoutDirection == CLAY_TOP_TO_BOTTOM);
            resizableContainerBuffer.length = 0;
            float parentChildGap = parentStyleConfig->childGap;

            for (int childOffset = 0; childOffset < parent->children.length; childOffset++) {
                int32_t childElementIndex = parent->children.elements[childOffset];
                Clay_LayoutElement *childElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, childElementIndex);
                Clay_SizingAxis childSizing = xAxis ? childElement->layoutConfig->sizing.width : childElement->layoutConfig->sizing.height;
                float childSize = xAxis ? childElement->dimensions.width : childElement->dimensions.height;

                if (!Clay__ElementHasConfig(childElement, CLAY__ELEMENT_CONFIG_TYPE_TEXT) && childElement->children.length > 0) {
                    Clay__int32_tArray_Add(&bfsBuffer, childElementIndex);
                }

                if (childSizing.type != CLAY__SIZING_TYPE_PERCENT && childSizing.type != CLAY__SIZING_TYPE_FIXED && (!Clay__ElementHasConfig(childElement, CLAY__ELEMENT_CONFIG_TYPE_TEXT) || (Clay__FindElementConfigWithType(childElement, CLAY__ELEMENT_CONFIG_TYPE_TEXT).textElementConfig->wrapMode == CLAY_TEXT_WRAP_WORDS))) {
                    Clay__int32_tArray_Add(&resizableContainerBuffer, childElementIndex);
                }

                if (sizingAlongAxis) {
                    innerContentSize += (childSizing.type == CLAY__SIZING_TYPE_PERCENT ? 0 : childSize);
                    if (childSizing.type == CLAY__SIZING_TYPE_GROW) {
                        growContainerContentSize += childSize;
                        growContainerCount++;
                    }
                    if (childOffset > 0) {
                        innerContentSize += parentChildGap; // For children after index 0, the childAxisOffset is the gap from the previous child
                        totalPaddingAndChildGaps += parentChildGap;
                    }
                } else {
                    innerContentSize = CLAY__MAX(childSize, innerContentSize);
                }
            }

            // Expand percentage containers to size
            for (int childOffset = 0; childOffset < parent->children.length; childOffset++) {
                int32_t childElementIndex = parent->children.elements[childOffset];
                Clay_LayoutElement *childElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, childElementIndex);
                Clay_SizingAxis childSizing = xAxis ? childElement->layoutConfig->sizing.width : childElement->layoutConfig->sizing.height;
                float *childSize = xAxis ? &childElement->dimensions.width : &childElement->dimensions.height;
                if (childSizing.type == CLAY__SIZING_TYPE_PERCENT) {
                    *childSize = (parentSize - totalPaddingAndChildGaps) * childSizing.sizePercent;
                    if (sizingAlongAxis) {
                        innerContentSize += *childSize;
                        if (childOffset > 0) {
                            innerContentSize += parentChildGap; // For children after index 0, the childAxisOffset is the gap from the previous child
                            totalPaddingAndChildGaps += parentChildGap;
                        }
                    } else {
                        innerContentSize = CLAY__MAX(*childSize, innerContentSize);
                    }
                }
            }

            if (sizingAlongAxis) {
                float sizeToDistribute = parentSize - parentPadding * 2 - innerContentSize;
                // If the content is too large, compress the children as much as possible
                if (sizeToDistribute < 0) {
                    // If the parent can scroll in the axis direction in this direction, don't compress children, just leave them alone
                    if (Clay__ElementHasConfig(parent, CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER)) {
                        Clay_ScrollElementConfig *scrollElementConfig = Clay__FindElementConfigWithType(parent, CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER).scrollElementConfig;
                        if (((xAxis && scrollElementConfig->horizontal) || (!xAxis && scrollElementConfig->vertical))) {
                            continue;
                        }
                    }
                    // Scrolling containers preferentially compress before others
                    sizeToDistribute = Clay__DistributeSizeAmongChildren(xAxis, sizeToDistribute, resizableContainerBuffer, CLAY__SIZE_DISTRIBUTION_TYPE_SCROLL_CONTAINER);

                    // If there is still height to make up, remove it from all containers that haven't hit their minimum size
                    if (sizeToDistribute < 0) {
                        Clay__DistributeSizeAmongChildren(xAxis, sizeToDistribute, resizableContainerBuffer, CLAY__SIZE_DISTRIBUTION_TYPE_RESIZEABLE_CONTAINER);
                    }
                // The content is too small, allow SIZING_GROW containers to expand
                } else if (sizeToDistribute > 0 && growContainerCount > 0) {
                    float targetSize = (sizeToDistribute + growContainerContentSize) / growContainerCount;
                    for (int childOffset = 0; childOffset < resizableContainerBuffer.length; childOffset++) {
                        Clay_LayoutElement *childElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, Clay__int32_tArray_Get(&resizableContainerBuffer, childOffset));
                        Clay_SizingAxis childSizing = xAxis ? childElement->layoutConfig->sizing.width : childElement->layoutConfig->sizing.height;
                        if (childSizing.type == CLAY__SIZING_TYPE_GROW) {
                            float *childSize = xAxis ? &childElement->dimensions.width : &childElement->dimensions.height;
                            float *minSize = xAxis ? &childElement->minDimensions.width : &childElement->minDimensions.height;
                            if (targetSize < *minSize) {
                                growContainerContentSize -= *minSize;
                                Clay__int32_tArray_RemoveSwapback(&resizableContainerBuffer, childOffset);
                                growContainerCount--;
                                targetSize = (sizeToDistribute + growContainerContentSize) / growContainerCount;
                                childOffset = -1;
                                continue;
                            }
                            *childSize = targetSize;
                        }
                    }
                }
            // Sizing along the non layout axis ("off axis")
            } else {
                for (int childOffset = 0; childOffset < resizableContainerBuffer.length; childOffset++) {
                    Clay_LayoutElement *childElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, Clay__int32_tArray_Get(&resizableContainerBuffer, childOffset));
                    Clay_SizingAxis childSizing = xAxis ? childElement->layoutConfig->sizing.width : childElement->layoutConfig->sizing.height;
                    float *childSize = xAxis ? &childElement->dimensions.width : &childElement->dimensions.height;

                    if (!xAxis && Clay__ElementHasConfig(childElement, CLAY__ELEMENT_CONFIG_TYPE_IMAGE)) {
                        continue; // Currently we don't support resizing aspect ratio images on the Y axis because it would break the ratio
                    }

                    // If we're laying out the children of a scroll panel, grow containers expand to the height of the inner content, not the outer container
                    float maxSize = parentSize - parentPadding * 2;
                    if (Clay__ElementHasConfig(parent, CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER)) {
                        Clay_ScrollElementConfig *scrollElementConfig = Clay__FindElementConfigWithType(parent, CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER).scrollElementConfig;
                        if (((xAxis && scrollElementConfig->horizontal) || (!xAxis && scrollElementConfig->vertical))) {
                            maxSize = CLAY__MAX(maxSize, innerContentSize);
                        }
                    }
                    if (childSizing.type == CLAY__SIZING_TYPE_FIT) {
                        *childSize = CLAY__MAX(childSizing.sizeMinMax.min, CLAY__MIN(*childSize, maxSize));
                    } else if (childSizing.type == CLAY__SIZING_TYPE_GROW) {
                        *childSize = CLAY__MIN(maxSize, childSizing.sizeMinMax.max);
                    }
                }
            }
        }
    }
}

void Clay__CalculateFinalLayout() {
    // Calculate sizing along the X axis
    Clay__SizeContainersAlongAxis(true);

    // Wrap text
    for (int textElementIndex = 0; textElementIndex < Clay__textElementData.length; ++textElementIndex) {
        Clay__TextElementData *textElementData = Clay__TextElementDataArray_Get(&Clay__textElementData, textElementIndex);
        textElementData->wrappedLines = CLAY__INIT(Clay__StringArraySlice) { .length = 0, .internalArray = &Clay__wrappedTextLines.internalArray[Clay__wrappedTextLines.length] };
        Clay_LayoutElement *containerElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, (int)textElementData->elementIndex);
        Clay_TextElementConfig *textConfig = Clay__FindElementConfigWithType(containerElement, CLAY__ELEMENT_CONFIG_TYPE_TEXT).textElementConfig;
        Clay__MeasureTextCacheItem *measureTextCacheItem = Clay__MeasureTextCached(&textElementData->text, textConfig);
        float lineWidth = 0;
        float lineHeight = textConfig->lineHeight > 0 ? textConfig->lineHeight : textElementData->preferredDimensions.height;
        uint32_t lineLengthChars = 0;
        uint32_t lineStartOffset = 0;
        if (textElementData->preferredDimensions.width <= containerElement->dimensions.width) {
            Clay__StringArray_Add(&Clay__wrappedTextLines, textElementData->text);
            textElementData->wrappedLines.length++;
            continue;
        }
        for (int wordIndex = 0; wordIndex < measureTextCacheItem->measuredWords.length; ++wordIndex) {
            Clay__MeasuredWord *measuredWord = Clay__MeasuredWordArraySlice_Get(&measureTextCacheItem->measuredWords, wordIndex);
            // Only word on the line is too large, just render it anyway
            if (lineLengthChars == 0 && lineWidth + measuredWord->width > containerElement->dimensions.width) {
                Clay__StringArray_Add(&Clay__wrappedTextLines, CLAY__INIT(Clay_String) {.length = (int)measuredWord->length, .chars = &textElementData->text.chars[measuredWord->startOffset] });
                textElementData->wrappedLines.length++;
            }
            // measuredWord->length == 0 means a newline character
            else if (measuredWord->length == 0 || lineWidth + measuredWord->width > containerElement->dimensions.width) {
                Clay__StringArray_Add(&Clay__wrappedTextLines, CLAY__INIT(Clay_String) {.length = (int)lineLengthChars, .chars = &textElementData->text.chars[lineStartOffset] });
                textElementData->wrappedLines.length++;
                if (lineLengthChars > 0 && measuredWord->length > 0) {
                    wordIndex--;
                }
                lineWidth = 0;
                lineLengthChars = 0;
                lineStartOffset = measuredWord->startOffset;
            } else {
                lineWidth += measuredWord->width;
                lineLengthChars += measuredWord->length;
            }
        }
        if (lineLengthChars > 0) {
            Clay__StringArray_Add(&Clay__wrappedTextLines, CLAY__INIT(Clay_String) {.length = (int)lineLengthChars, .chars = &textElementData->text.chars[lineStartOffset] });
            textElementData->wrappedLines.length++;
        }
        containerElement->dimensions.height = lineHeight * textElementData->wrappedLines.length;
    }

    // Scale vertical image heights according to aspect ratio
    for (int i = 0; i < Clay__imageElementPointers.length; ++i) {
        Clay_LayoutElement* imageElement = Clay__LayoutElementPointerArray_Get(&Clay__imageElementPointers, i);
        Clay_ImageElementConfig *config = Clay__FindElementConfigWithType(imageElement, CLAY__ELEMENT_CONFIG_TYPE_IMAGE).imageElementConfig;
        imageElement->dimensions.height = (config->sourceDimensions.height / CLAY__MAX(config->sourceDimensions.width, 1)) * imageElement->dimensions.width;
    }

    // Propagate effect of text wrapping, image aspect scaling etc. on height of parents
    Clay__LayoutElementTreeNodeArray dfsBuffer = Clay__layoutElementTreeNodeArray1;
    dfsBuffer.length = 0;
    for (int i = 0; i < Clay__layoutElementTreeRoots.length; ++i) {
        Clay__LayoutElementTreeRoot *root = Clay__LayoutElementTreeRootArray_Get(&Clay__layoutElementTreeRoots, i);
        Clay__treeNodeVisited.internalArray[dfsBuffer.length] = false;
        Clay__LayoutElementTreeNodeArray_Add(&dfsBuffer, CLAY__INIT(Clay__LayoutElementTreeNode) { .layoutElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, (int)root->layoutElementIndex) });
    }
    while (dfsBuffer.length > 0) {
        Clay__LayoutElementTreeNode *currentElementTreeNode = Clay__LayoutElementTreeNodeArray_Get(&dfsBuffer, (int)dfsBuffer.length - 1);
        Clay_LayoutElement *currentElement = currentElementTreeNode->layoutElement;
        if (!Clay__treeNodeVisited.internalArray[dfsBuffer.length - 1]) {
            Clay__treeNodeVisited.internalArray[dfsBuffer.length - 1] = true;
            // If the element has no children or is the container for a text element, don't bother inspecting it
            if (Clay__ElementHasConfig(currentElement, CLAY__ELEMENT_CONFIG_TYPE_TEXT) || currentElement->children.length == 0) {
                dfsBuffer.length--;
                continue;
            }
            // Add the children to the DFS buffer (needs to be pushed in reverse so that stack traversal is in correct layout order)
            for (int i = 0; i < currentElement->children.length; i++) {
                Clay__treeNodeVisited.internalArray[dfsBuffer.length] = false;
                Clay__LayoutElementTreeNodeArray_Add(&dfsBuffer, CLAY__INIT(Clay__LayoutElementTreeNode) { .layoutElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, currentElement->children.elements[i]) });
            }
            continue;
        }
        dfsBuffer.length--;

        // DFS node has been visited, this is on the way back up to the root
        Clay_LayoutConfig *layoutConfig = currentElement->layoutConfig;
        if (layoutConfig->sizing.height.type == CLAY__SIZING_TYPE_PERCENT) {
            continue;
        }
        if (layoutConfig->layoutDirection == CLAY_LEFT_TO_RIGHT) {
            // Resize any parent containers that have grown in height along their non layout axis
            for (int j = 0; j < currentElement->children.length; ++j) {
                Clay_LayoutElement *childElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, currentElement->children.elements[j]);
                float childHeightWithPadding = CLAY__MAX(childElement->dimensions.height + layoutConfig->padding.y * 2, currentElement->dimensions.height);
                currentElement->dimensions.height = CLAY__MIN(CLAY__MAX(childHeightWithPadding, layoutConfig->sizing.height.sizeMinMax.min), layoutConfig->sizing.height.sizeMinMax.max);
            }
        } else if (layoutConfig->layoutDirection == CLAY_TOP_TO_BOTTOM) {
            // Resizing along the layout axis
            float contentHeight = (float)layoutConfig->padding.y * 2;
            for (int j = 0; j < currentElement->children.length; ++j) {
                Clay_LayoutElement *childElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, currentElement->children.elements[j]);
                contentHeight += childElement->dimensions.height;
            }
            contentHeight += (float)(CLAY__MAX(currentElement->children.length - 1, 0) * layoutConfig->childGap);
            currentElement->dimensions.height = CLAY__MIN(CLAY__MAX(contentHeight, layoutConfig->sizing.height.sizeMinMax.min), layoutConfig->sizing.height.sizeMinMax.max);
        }
    }

    // Calculate sizing along the Y axis
    Clay__SizeContainersAlongAxis(false);

    // Calculate final positions and generate render commands
    Clay__renderCommands.length = 0;
    dfsBuffer.length = 0;
    for (int rootIndex = 0; rootIndex < Clay__layoutElementTreeRoots.length; ++rootIndex) {
        dfsBuffer.length = 0;
        Clay__LayoutElementTreeRoot *root = Clay__LayoutElementTreeRootArray_Get(&Clay__layoutElementTreeRoots, rootIndex);
        Clay_LayoutElement *rootElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, (int)root->layoutElementIndex);
        Clay_Vector2 rootPosition = CLAY__INIT(Clay_Vector2) {};
        Clay_LayoutElementHashMapItem *parentHashMapItem = Clay__GetHashMapItem(root->parentId);
        // Position root floating containers
        if (Clay__ElementHasConfig(rootElement, CLAY__ELEMENT_CONFIG_TYPE_FLOATING_CONTAINER) && parentHashMapItem) {
            Clay_FloatingElementConfig *config = Clay__FindElementConfigWithType(rootElement, CLAY__ELEMENT_CONFIG_TYPE_FLOATING_CONTAINER).floatingElementConfig;
            Clay_Dimensions rootDimensions = rootElement->dimensions;
            Clay_BoundingBox parentBoundingBox = parentHashMapItem->boundingBox;
            // Set X position
            Clay_Vector2 targetAttachPosition = CLAY__INIT(Clay_Vector2){};
            switch (config->attachment.parent) {
                case CLAY_ATTACH_POINT_LEFT_TOP:
                case CLAY_ATTACH_POINT_LEFT_CENTER:
                case CLAY_ATTACH_POINT_LEFT_BOTTOM: targetAttachPosition.x = parentBoundingBox.x; break;
                case CLAY_ATTACH_POINT_CENTER_TOP:
                case CLAY_ATTACH_POINT_CENTER_CENTER:
                case CLAY_ATTACH_POINT_CENTER_BOTTOM: targetAttachPosition.x = parentBoundingBox.x + (parentBoundingBox.width / 2); break;
                case CLAY_ATTACH_POINT_RIGHT_TOP:
                case CLAY_ATTACH_POINT_RIGHT_CENTER:
                case CLAY_ATTACH_POINT_RIGHT_BOTTOM: targetAttachPosition.x = parentBoundingBox.x + parentBoundingBox.width; break;
            }
            switch (config->attachment.element) {
                case CLAY_ATTACH_POINT_LEFT_TOP:
                case CLAY_ATTACH_POINT_LEFT_CENTER:
                case CLAY_ATTACH_POINT_LEFT_BOTTOM: break;
                case CLAY_ATTACH_POINT_CENTER_TOP:
                case CLAY_ATTACH_POINT_CENTER_CENTER:
                case CLAY_ATTACH_POINT_CENTER_BOTTOM: targetAttachPosition.x -= (rootDimensions.width / 2); break;
                case CLAY_ATTACH_POINT_RIGHT_TOP:
                case CLAY_ATTACH_POINT_RIGHT_CENTER:
                case CLAY_ATTACH_POINT_RIGHT_BOTTOM: targetAttachPosition.x -= rootDimensions.width; break;
            }
            switch (config->attachment.parent) { // I know I could merge the x and y switch statements, but this is easier to read
                case CLAY_ATTACH_POINT_LEFT_TOP:
                case CLAY_ATTACH_POINT_RIGHT_TOP:
                case CLAY_ATTACH_POINT_CENTER_TOP: targetAttachPosition.y = parentBoundingBox.y; break;
                case CLAY_ATTACH_POINT_LEFT_CENTER:
                case CLAY_ATTACH_POINT_CENTER_CENTER:
                case CLAY_ATTACH_POINT_RIGHT_CENTER: targetAttachPosition.y = parentBoundingBox.y + (parentBoundingBox.height / 2); break;
                case CLAY_ATTACH_POINT_LEFT_BOTTOM:
                case CLAY_ATTACH_POINT_CENTER_BOTTOM:
                case CLAY_ATTACH_POINT_RIGHT_BOTTOM: targetAttachPosition.y = parentBoundingBox.y + parentBoundingBox.height; break;
            }
            switch (config->attachment.element) {
                case CLAY_ATTACH_POINT_LEFT_TOP:
                case CLAY_ATTACH_POINT_RIGHT_TOP:
                case CLAY_ATTACH_POINT_CENTER_TOP: break;
                case CLAY_ATTACH_POINT_LEFT_CENTER:
                case CLAY_ATTACH_POINT_CENTER_CENTER:
                case CLAY_ATTACH_POINT_RIGHT_CENTER: targetAttachPosition.y -= (rootDimensions.height / 2); break;
                case CLAY_ATTACH_POINT_LEFT_BOTTOM:
                case CLAY_ATTACH_POINT_CENTER_BOTTOM:
                case CLAY_ATTACH_POINT_RIGHT_BOTTOM: targetAttachPosition.y -= rootDimensions.height; break;
            }
            targetAttachPosition.x += config->offset.x;
            targetAttachPosition.y += config->offset.y;
            rootPosition = targetAttachPosition;
        }
        if (root->clipElementId) {
            Clay_LayoutElementHashMapItem *clipHashMapItem = Clay__GetHashMapItem(root->clipElementId);
            if (clipHashMapItem) {
                Clay_RenderCommandArray_Add(&Clay__renderCommands, CLAY__INIT(Clay_RenderCommand) {
                    .boundingBox = clipHashMapItem->boundingBox,
                    .id = Clay__RehashWithNumber(rootElement->id, 10), // TODO need a better strategy for managing derived ids
                    .commandType = CLAY_RENDER_COMMAND_TYPE_SCISSOR_START,
                });
            }
        }
        Clay__LayoutElementTreeNodeArray_Add(&dfsBuffer, CLAY__INIT(Clay__LayoutElementTreeNode) { .layoutElement = rootElement, .position = rootPosition, .nextChildOffset = CLAY__INIT(Clay_Vector2) { .x = (float)rootElement->layoutConfig->padding.x, .y = (float)rootElement->layoutConfig->padding.y } });

        Clay__treeNodeVisited.internalArray[0] = false;
        while (dfsBuffer.length > 0) {
            Clay__LayoutElementTreeNode *currentElementTreeNode = Clay__LayoutElementTreeNodeArray_Get(&dfsBuffer, (int)dfsBuffer.length - 1);
            Clay_LayoutElement *currentElement = currentElementTreeNode->layoutElement;
            Clay_LayoutConfig *layoutConfig = currentElement->layoutConfig;
            Clay_Vector2 scrollOffset = {0};

            // This will only be run a single time for each element in downwards DFS order
            if (!Clay__treeNodeVisited.internalArray[dfsBuffer.length - 1]) {
                Clay__treeNodeVisited.internalArray[dfsBuffer.length - 1] = true;

                Clay_BoundingBox currentElementBoundingBox = CLAY__INIT(Clay_BoundingBox) { currentElementTreeNode->position.x, currentElementTreeNode->position.y, currentElement->dimensions.width, currentElement->dimensions.height };
                if (Clay__ElementHasConfig(currentElement, CLAY__ELEMENT_CONFIG_TYPE_FLOATING_CONTAINER)) {
                    Clay_FloatingElementConfig *floatingElementConfig = Clay__FindElementConfigWithType(currentElement, CLAY__ELEMENT_CONFIG_TYPE_FLOATING_CONTAINER).floatingElementConfig;
                    Clay_Dimensions expand = floatingElementConfig->expand;
                    currentElementBoundingBox.x -= expand.width;
                    currentElementBoundingBox.width += expand.width * 2;
                    currentElementBoundingBox.y -= expand.height;
                    currentElementBoundingBox.height += expand.height * 2;
                }

                Clay__ScrollContainerDataInternal *scrollContainerData = CLAY__NULL;
                // Apply scroll offsets to container
                if (Clay__ElementHasConfig(currentElement, CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER)) {
                    Clay_ScrollElementConfig *scrollConfig = Clay__FindElementConfigWithType(currentElement, CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER).scrollElementConfig;

                    // This linear scan could theoretically be slow under very strange conditions, but I can't imagine a real UI with more than a few 10's of scroll containers
                    for (int i = 0; i < Clay__scrollContainerDatas.length; i++) {
                        Clay__ScrollContainerDataInternal *mapping = Clay__ScrollContainerDataInternalArray_Get(&Clay__scrollContainerDatas, i);
                        if (mapping->layoutElement == currentElement) {
                            scrollContainerData = mapping;
                            mapping->boundingBox = currentElementBoundingBox;
                            if (scrollConfig->horizontal) {
                                scrollOffset.x = mapping->scrollPosition.x;
                            }
                            if (scrollConfig->vertical) {
                                scrollOffset.y = mapping->scrollPosition.y;
                            }
                            break;
                        }
                    }
                }

                Clay_LayoutElementHashMapItem *hashMapItem = Clay__GetHashMapItem(currentElement->id);
                if (hashMapItem) {
                    hashMapItem->boundingBox = currentElementBoundingBox;
                }

                int sortedConfigIndexes[20];
                for (int elementConfigIndex = 0; elementConfigIndex < currentElement->elementConfigs.length; ++elementConfigIndex) {
                    sortedConfigIndexes[elementConfigIndex] = elementConfigIndex;
                }
                int sortMax = currentElement->elementConfigs.length - 1;
                while (sortMax > 0) { // dumb bubble sort
                    for (int i = 0; i < sortMax; ++i) {
                        int current = sortedConfigIndexes[i];
                        int next = sortedConfigIndexes[i + 1];
                        Clay__ElementConfigType currentType = Clay__ElementConfigArraySlice_Get(&currentElement->elementConfigs, current)->type;
                        Clay__ElementConfigType nextType = Clay__ElementConfigArraySlice_Get(&currentElement->elementConfigs, next)->type;
                        if (nextType == CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER || currentType == CLAY__ELEMENT_CONFIG_TYPE_BORDER_CONTAINER) {
                            sortedConfigIndexes[i] = next;
                            sortedConfigIndexes[i + 1] = current;
                        }
                    }
                    sortMax--;
                }

                // Create the render commands for this element
                for (int elementConfigIndex = 0; elementConfigIndex < currentElement->elementConfigs.length; ++elementConfigIndex) {
                    Clay_ElementConfig *elementConfig = Clay__ElementConfigArraySlice_Get(&currentElement->elementConfigs, sortedConfigIndexes[elementConfigIndex]);
                    Clay_RenderCommand renderCommand = CLAY__INIT(Clay_RenderCommand) {
                        .boundingBox = currentElementBoundingBox,
                        .config = elementConfig->config,
                        .id = currentElement->id,
                    };

                    #ifndef CLAY_DISABLE_CULLING
                    // Culling - Don't bother to generate render commands for rectangles entirely outside the screen - this won't stop their children from being rendered if they overflow
                    bool offscreen = currentElementBoundingBox.x > (float)Clay__layoutDimensions.width || currentElementBoundingBox.y > (float)Clay__layoutDimensions.height || currentElementBoundingBox.x + currentElementBoundingBox.width < 0 || currentElementBoundingBox.y + currentElementBoundingBox.height < 0;
                    bool shouldRender = !offscreen;
                    #elif
                    bool shouldRender = true;
                    #endif
                    switch (elementConfig->type) {
                        case CLAY__ELEMENT_CONFIG_TYPE_RECTANGLE: {
                            renderCommand.commandType = CLAY_RENDER_COMMAND_TYPE_RECTANGLE;
                            break;
                        }
                        case CLAY__ELEMENT_CONFIG_TYPE_BORDER_CONTAINER: {
                            renderCommand.commandType = CLAY_RENDER_COMMAND_TYPE_BORDER;
                            break;
                        }
                        case CLAY__ELEMENT_CONFIG_TYPE_FLOATING_CONTAINER: {
                            renderCommand.commandType = CLAY_RENDER_COMMAND_TYPE_NONE;
                            shouldRender = false;
                            break;
                        }
                        case CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER: {
                            renderCommand.commandType = CLAY_RENDER_COMMAND_TYPE_SCISSOR_START;
                            break;
                        }
                        case CLAY__ELEMENT_CONFIG_TYPE_IMAGE: {
                            renderCommand.commandType = CLAY_RENDER_COMMAND_TYPE_IMAGE;
                            break;
                        }
                        case CLAY__ELEMENT_CONFIG_TYPE_TEXT: {
                            shouldRender = false;
                            Clay_ElementConfigUnion configUnion = elementConfig->config;
                            Clay_TextElementConfig *textElementConfig = configUnion.textElementConfig;
                            float naturalLineHeight = currentElement->textElementData->preferredDimensions.height;
                            float finalLineHeight = textElementConfig->lineHeight > 0 ? textElementConfig->lineHeight : naturalLineHeight;
                            float lineHeightOffset = (finalLineHeight - naturalLineHeight) / 2;
                            float yPosition = lineHeightOffset;
                            for (int lineIndex = 0; lineIndex < currentElement->textElementData->wrappedLines.length; ++lineIndex) {
                                Clay_String wrappedLine = currentElement->textElementData->wrappedLines.internalArray[lineIndex]; // todo range check
                                if (wrappedLine.length == 0) {
                                    continue;
                                }
                                Clay_RenderCommandArray_Add(&Clay__renderCommands, CLAY__INIT(Clay_RenderCommand) {
                                    .boundingBox = { currentElementBoundingBox.x, currentElementBoundingBox.y + yPosition, currentElement->dimensions.width, naturalLineHeight }, // TODO width
                                    .config = configUnion,
                                    .text = wrappedLine,
                                    .id = Clay__HashNumber(lineIndex, currentElement->id).id,
                                    .commandType = CLAY_RENDER_COMMAND_TYPE_TEXT,
                                });
                                yPosition += finalLineHeight;

                                if (currentElementBoundingBox.y + yPosition > Clay__layoutDimensions.height) {
                                    break;
                                }
                            }
                            break;
                        }
                        case CLAY__ELEMENT_CONFIG_TYPE_CUSTOM: {
                            renderCommand.commandType = CLAY_RENDER_COMMAND_TYPE_CUSTOM;
                            break;
                        }
                        default: break;
                    }
                    if (shouldRender) {
                        Clay_RenderCommandArray_Add(&Clay__renderCommands, renderCommand);
                    }
                    if (offscreen) {
                        // NOTE: You may be tempted to try an early return / continue if an element is off screen. Why bother calculating layout for its children, right?
                        // Unfortunately, a FLOATING_CONTAINER may be defined that attaches to a child or grandchild of this element, which is large enough to still
                        // be on screen, even if this element isn't. That depends on this element and it's children being laid out correctly (even if they are entirely off screen)
                    }
                }

                // Setup initial on-axis alignment
                if (!Clay__ElementHasConfig(currentElementTreeNode->layoutElement, CLAY__ELEMENT_CONFIG_TYPE_TEXT)) {
                    Clay_Dimensions contentSize = CLAY__INIT(Clay_Dimensions) {0,0};
                    if (layoutConfig->layoutDirection == CLAY_LEFT_TO_RIGHT) {
                        for (int i = 0; i < currentElement->children.length; ++i) {
                            Clay_LayoutElement *childElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, currentElement->children.elements[i]);
                            contentSize.width += childElement->dimensions.width;
                            contentSize.height = CLAY__MAX(contentSize.height, childElement->dimensions.height);
                        }
                        contentSize.width += (float)(CLAY__MAX(currentElement->children.length - 1, 0) * layoutConfig->childGap);
                        float extraSpace = currentElement->dimensions.width - (float)layoutConfig->padding.x * 2 - contentSize.width;
                        switch (layoutConfig->childAlignment.x) {
                            case CLAY_ALIGN_X_LEFT: extraSpace = 0; break;
                            case CLAY_ALIGN_X_CENTER: extraSpace /= 2; break;
                            default: break;
                        }
                        currentElementTreeNode->nextChildOffset.x += extraSpace;
                    } else {
                        for (int i = 0; i < currentElement->children.length; ++i) {
                            Clay_LayoutElement *childElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, currentElement->children.elements[i]);
                            contentSize.width = CLAY__MAX(contentSize.width, childElement->dimensions.width);
                            contentSize.height += childElement->dimensions.height;
                        }
                        contentSize.height += (float)(CLAY__MAX(currentElement->children.length - 1, 0) * layoutConfig->childGap);
                        float extraSpace = currentElement->dimensions.height - (float)layoutConfig->padding.y * 2 - contentSize.height;
                        switch (layoutConfig->childAlignment.y) {
                            case CLAY_ALIGN_Y_TOP: extraSpace = 0; break;
                            case CLAY_ALIGN_Y_CENTER: extraSpace /= 2; break;
                            default: break;
                        }
                        currentElementTreeNode->nextChildOffset.y += extraSpace;
                    }

                    if (scrollContainerData) {
                        scrollContainerData->contentSize = CLAY__INIT(Clay_Dimensions) { contentSize.width + layoutConfig->padding.x * 2, contentSize.height + layoutConfig->padding.y * 2 };
                    }
                }
            }
            else {
                // DFS is returning upwards backwards
                bool closeScrollElement = false;
                if (Clay__ElementHasConfig(currentElement, CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER)) {
                    closeScrollElement = true;
                    Clay_ScrollElementConfig *scrollConfig = Clay__FindElementConfigWithType(currentElement, CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER).scrollElementConfig;
                    // todo get rid of this annoying duplication just for handling borders between elements
                    for (int i = 0; i < Clay__scrollContainerDatas.length; i++) {
                        Clay__ScrollContainerDataInternal *mapping = Clay__ScrollContainerDataInternalArray_Get(&Clay__scrollContainerDatas, i);
                        if (mapping->layoutElement == currentElement) {
                            if (scrollConfig->horizontal) { scrollOffset.x = mapping->scrollPosition.x; }
                            if (scrollConfig->vertical) { scrollOffset.y = mapping->scrollPosition.y; }
                            break;
                        }
                    }
                }
                if (Clay__ElementHasConfig(currentElement, CLAY__ELEMENT_CONFIG_TYPE_BORDER_CONTAINER)) {
                    Clay_LayoutElementHashMapItem *currentElementData = Clay__GetHashMapItem(currentElement->id);
                    Clay_BoundingBox currentElementBoundingBox = currentElementData->boundingBox;
                    Clay_BorderElementConfig *borderConfig = Clay__FindElementConfigWithType(currentElement, CLAY__ELEMENT_CONFIG_TYPE_BORDER_CONTAINER).borderElementConfig;
                    if (borderConfig->betweenChildren.width > 0 && borderConfig->betweenChildren.color.a > 0) {
                        Clay_RectangleElementConfig *rectangleConfig = Clay__StoreRectangleElementConfig(CLAY__INIT(Clay_RectangleElementConfig) {.color = borderConfig->betweenChildren.color});
                        Clay_Vector2 borderOffset = { (float)layoutConfig->padding.x, (float)layoutConfig->padding.y };
                        if (layoutConfig->layoutDirection == CLAY_LEFT_TO_RIGHT) {
                            for (int i = 0; i < currentElement->children.length; ++i) {
                                Clay_LayoutElement *childElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, currentElement->children.elements[i]);
                                if (i > 0) {
                                    Clay_RenderCommandArray_Add(&Clay__renderCommands, CLAY__INIT(Clay_RenderCommand) {
                                        .boundingBox = { currentElementBoundingBox.x + borderOffset.x + scrollOffset.x, currentElementBoundingBox.y + scrollOffset.y, (float)borderConfig->betweenChildren.width, currentElement->dimensions.height },
                                        .config = { rectangleConfig },
                                        .id = Clay__RehashWithNumber(currentElement->id, 5 + i),
                                        .commandType = CLAY_RENDER_COMMAND_TYPE_RECTANGLE,
                                    });
                                }
                                borderOffset.x += (childElement->dimensions.width + (float)layoutConfig->childGap / 2);
                            }
                        } else {
                            for (int i = 0; i < currentElement->children.length; ++i) {
                                Clay_LayoutElement *childElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, currentElement->children.elements[i]);
                                if (i > 0) {
                                    Clay_RenderCommandArray_Add(&Clay__renderCommands, CLAY__INIT(Clay_RenderCommand) {
                                        .boundingBox = { currentElementBoundingBox.x + scrollOffset.x, currentElementBoundingBox.y + borderOffset.y + scrollOffset.y, currentElement->dimensions.width, (float)borderConfig->betweenChildren.width },
                                        .config = { rectangleConfig },
                                        .id = Clay__RehashWithNumber(currentElement->id, 5 + i),
                                        .commandType = CLAY_RENDER_COMMAND_TYPE_RECTANGLE,
                                    });
                                }
                                borderOffset.y += (childElement->dimensions.height + (float)layoutConfig->childGap / 2);
                            }
                        }
                    }
                }
                // This exists because the scissor needs to end _after_ borders between elements
                if (closeScrollElement) {
                    Clay_RenderCommandArray_Add(&Clay__renderCommands, CLAY__INIT(Clay_RenderCommand) {
                        .id = Clay__RehashWithNumber(currentElement->id, 11),
                       .commandType = CLAY_RENDER_COMMAND_TYPE_SCISSOR_END,
                    });
                }

                dfsBuffer.length--;
                continue;
            }

            // Add children to the DFS buffer
            if (!Clay__ElementHasConfig(currentElement, CLAY__ELEMENT_CONFIG_TYPE_TEXT)) {
                dfsBuffer.length += currentElement->children.length;
                for (int i = 0; i < currentElement->children.length; ++i) {
                    Clay_LayoutElement *childElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, currentElement->children.elements[i]);
                    // Alignment along non layout axis
                    if (layoutConfig->layoutDirection == CLAY_LEFT_TO_RIGHT) {
                        currentElementTreeNode->nextChildOffset.y = currentElement->layoutConfig->padding.y;
                        float whiteSpaceAroundChild = currentElement->dimensions.height - (float)currentElement->layoutConfig->padding.y * 2 - childElement->dimensions.height;
                        switch (layoutConfig->childAlignment.y) {
                            case CLAY_ALIGN_Y_TOP: break;
                            case CLAY_ALIGN_Y_CENTER: currentElementTreeNode->nextChildOffset.y += whiteSpaceAroundChild / 2; break;
                            case CLAY_ALIGN_Y_BOTTOM: currentElementTreeNode->nextChildOffset.y += whiteSpaceAroundChild; break;
                        }
                    } else {
                        currentElementTreeNode->nextChildOffset.x = currentElement->layoutConfig->padding.x;
                        float whiteSpaceAroundChild = currentElement->dimensions.width - (float)currentElement->layoutConfig->padding.x * 2 - childElement->dimensions.width;
                        switch (layoutConfig->childAlignment.x) {
                            case CLAY_ALIGN_X_LEFT: break;
                            case CLAY_ALIGN_X_CENTER: currentElementTreeNode->nextChildOffset.x += whiteSpaceAroundChild / 2; break;
                            case CLAY_ALIGN_X_RIGHT: currentElementTreeNode->nextChildOffset.x += whiteSpaceAroundChild; break;
                        }
                    }

                    Clay_Vector2 childPosition = CLAY__INIT(Clay_Vector2) {
                        currentElementTreeNode->position.x + currentElementTreeNode->nextChildOffset.x + scrollOffset.x,
                        currentElementTreeNode->position.y + currentElementTreeNode->nextChildOffset.y + scrollOffset.y,
                    };

                    // DFS buffer elements need to be added in reverse because stack traversal happens backwards
                    uint32_t newNodeIndex = dfsBuffer.length - 1 - i;
                    dfsBuffer.internalArray[newNodeIndex] = CLAY__INIT(Clay__LayoutElementTreeNode) {
                        .layoutElement = childElement,
                        .position = CLAY__INIT(Clay_Vector2) { childPosition.x, childPosition.y },
                        .nextChildOffset = CLAY__INIT(Clay_Vector2) { .x = (float)childElement->layoutConfig->padding.x, .y = (float)childElement->layoutConfig->padding.y },
                    };
                    Clay__treeNodeVisited.internalArray[newNodeIndex] = false;

                    // Update parent offsets
                    if (layoutConfig->layoutDirection == CLAY_LEFT_TO_RIGHT) {
                        currentElementTreeNode->nextChildOffset.x += childElement->dimensions.width + (float)layoutConfig->childGap;
                    } else {
                        currentElementTreeNode->nextChildOffset.y += childElement->dimensions.height + (float)layoutConfig->childGap;
                    }
                }
            }
        }

        if (root->clipElementId) {
            Clay_RenderCommandArray_Add(&Clay__renderCommands, CLAY__INIT(Clay_RenderCommand) { .id = Clay__RehashWithNumber(rootElement->id, 11), .commandType = CLAY_RENDER_COMMAND_TYPE_SCISSOR_END });
        }
    }
}

void Clay__AttachId(Clay_ElementId elementId) {
    Clay_LayoutElement *openLayoutElement = Clay__GetOpenLayoutElement();
    openLayoutElement->id = elementId.id;
    Clay__AddHashMapItem(elementId, openLayoutElement);
    Clay__StringArray_Add(&Clay__layoutElementIdStrings, elementId.stringId);
    #ifdef CLAY_DEBUG
    openLayoutElement->name = elementId.stringId;
    #endif
}

void Clay__AttachLayoutConfig(Clay_LayoutConfig *config) {
    Clay__GetOpenLayoutElement()->layoutConfig = config;
}
void Clay__AttachElementConfig(Clay_ElementConfigUnion config, Clay__ElementConfigType type) {
    Clay_LayoutElement *openLayoutElement = Clay__GetOpenLayoutElement();
    openLayoutElement->elementConfigs.length++;
    Clay__ElementConfigArray_Add(&Clay__elementConfigBuffer, CLAY__INIT(Clay_ElementConfig) { .type = type, .config = config });
}
inline Clay_LayoutConfig * Clay__StoreLayoutConfig(Clay_LayoutConfig config) { return Clay__LayoutConfigArray_Add(&Clay__layoutConfigs, config); }
inline Clay_RectangleElementConfig * Clay__StoreRectangleElementConfig(Clay_RectangleElementConfig config) { return Clay__RectangleElementConfigArray_Add(&Clay__rectangleElementConfigs, config); }
inline Clay_TextElementConfig * Clay__StoreTextElementConfig(Clay_TextElementConfig config) { return Clay__TextElementConfigArray_Add(&Clay__textElementConfigs, config); }
inline Clay_ImageElementConfig * Clay__StoreImageElementConfig(Clay_ImageElementConfig config) { return Clay__ImageElementConfigArray_Add(&Clay__imageElementConfigs, config); }
inline Clay_FloatingElementConfig * Clay__StoreFloatingElementConfig(Clay_FloatingElementConfig config) { return Clay__FloatingElementConfigArray_Add(&Clay__floatingElementConfigs, config); }
inline Clay_CustomElementConfig * Clay__StoreCustomElementConfig(Clay_CustomElementConfig config) { return Clay__CustomElementConfigArray_Add(&Clay__customElementConfigs, config); }
inline Clay_ScrollElementConfig * Clay__StoreScrollElementConfig(Clay_ScrollElementConfig config) { return Clay__ScrollElementConfigArray_Add(&Clay__scrollElementConfigs, config); }
inline Clay_BorderElementConfig * Clay__StoreBorderElementConfig(Clay_BorderElementConfig config) { return Clay__BorderElementConfigArray_Add(&Clay__borderElementConfigs, config); }

#pragma region DebugTools
Clay_Color CLAY__DEBUGVIEW_COLOR_1 = CLAY__INIT(Clay_Color) {58, 56, 52, 255};
Clay_Color CLAY__DEBUGVIEW_COLOR_2 = CLAY__INIT(Clay_Color) {62, 60, 58, 255};
Clay_Color CLAY__DEBUGVIEW_COLOR_3 = CLAY__INIT(Clay_Color) {141, 133, 135, 255};
Clay_Color CLAY__DEBUGVIEW_COLOR_4 = CLAY__INIT(Clay_Color) {238, 226, 231, 255};
Clay_Color CLAY__DEBUGVIEW_COLOR_SELECTED_ROW = CLAY__INIT(Clay_Color) {102, 80, 78, 255};
const int CLAY__DEBUGVIEW_ROW_HEIGHT = 30;
const int CLAY__DEBUGVIEW_OUTER_PADDING = 10;
const int CLAY__DEBUGVIEW_INDENT_WIDTH = 16;
Clay_TextElementConfig Clay__DebugView_TextNameConfig = CLAY__INIT(Clay_TextElementConfig) {.textColor = {238, 226, 231, 255}, .fontSize = 16, .wrapMode = CLAY_TEXT_WRAP_NONE };
Clay_LayoutConfig Clay__DebugView_ScrollViewItemLayoutConfig = CLAY__INIT(Clay_LayoutConfig) {};

Clay_String Clay__IntToString(int integer) {
    if (integer == 0) {
        return CLAY__INIT(Clay_String) { .length = 1, .chars = "0" };
    }
    char *chars = (char *)(Clay__dynamicStringData.internalArray + Clay__dynamicStringData.length);
    int length = 0;
    int sign = integer;

    if (integer < 0) {
        integer = -integer;
    }
    while (integer > 0) {
        chars[length++] = (char)(integer % 10 + '0');
        integer /= 10;
    }

    if (sign < 0) {
        chars[length++] = '-';
    }

    // Reverse the string to get the correct order
    for (int j = 0, k = length - 1; j < k; j++, k--) {
        char temp = chars[j];
        chars[j] = chars[k];
        chars[k] = temp;
    }
    Clay__dynamicStringData.length += length;
    return CLAY__INIT(Clay_String) { .length = length, .chars = chars };
}

typedef struct
{
    Clay_String label;
    Clay_Color color;
} Clay__DebugElementConfigTypeLabelConfig;

Clay__DebugElementConfigTypeLabelConfig Clay__DebugGetElementConfigTypeLabel(Clay__ElementConfigType type) {
    switch (type) {
        case CLAY__ELEMENT_CONFIG_TYPE_RECTANGLE: return CLAY__INIT(Clay__DebugElementConfigTypeLabelConfig) { CLAY_STRING("Rectangle"), CLAY__INIT(Clay_Color) {243,134,48,255} };
        case CLAY__ELEMENT_CONFIG_TYPE_TEXT: return CLAY__INIT(Clay__DebugElementConfigTypeLabelConfig) { CLAY_STRING("Text"), CLAY__INIT(Clay_Color) {105,210,231,255} };
        case CLAY__ELEMENT_CONFIG_TYPE_IMAGE: return CLAY__INIT(Clay__DebugElementConfigTypeLabelConfig) { CLAY_STRING("Image"), CLAY__INIT(Clay_Color) {121,189,154,255} };
        case CLAY__ELEMENT_CONFIG_TYPE_FLOATING_CONTAINER: return CLAY__INIT(Clay__DebugElementConfigTypeLabelConfig) { CLAY_STRING("Floating"), CLAY__INIT(Clay_Color) {250,105,0,255} };
        case CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER: return CLAY__INIT(Clay__DebugElementConfigTypeLabelConfig) { CLAY_STRING("Scroll"), CLAY__INIT(Clay_Color) {242,196,90,255} };
        case CLAY__ELEMENT_CONFIG_TYPE_BORDER_CONTAINER: return CLAY__INIT(Clay__DebugElementConfigTypeLabelConfig) { CLAY_STRING("Border"), CLAY__INIT(Clay_Color) {108,91,123, 255} };
        case CLAY__ELEMENT_CONFIG_TYPE_CUSTOM: return CLAY__INIT(Clay__DebugElementConfigTypeLabelConfig) { CLAY_STRING("Custom"), CLAY__INIT(Clay_Color) {11,72,107,255} };
    }
    return CLAY__INIT(Clay__DebugElementConfigTypeLabelConfig) { CLAY_STRING("Error"), CLAY__INIT(Clay_Color) {0,0,0,255} };
}

typedef struct
{
    uint32_t rowCount;
    uint32_t selectedElementRowIndex;
} Clay__RenderDebugLayoutData;

// Returns row count
Clay__RenderDebugLayoutData Clay__RenderDebugLayoutElementsList(int32_t initialRootsLength, int32_t highlightedRowIndex) {
    Clay__int32_tArray dfsBuffer = Clay__reusableElementIndexBuffer;
    Clay__DebugView_ScrollViewItemLayoutConfig = CLAY__INIT(Clay_LayoutConfig) { .sizing = { .height = CLAY_SIZING_FIXED(CLAY__DEBUGVIEW_ROW_HEIGHT) }, .childGap = 6, .childAlignment = { .y = CLAY_ALIGN_Y_CENTER }};
    Clay__RenderDebugLayoutData layoutData = {};

    uint32_t highlightedElementId = 0;

    for (int rootIndex = 0; rootIndex < initialRootsLength; ++rootIndex) {
        dfsBuffer.length = 0;
        Clay__LayoutElementTreeRoot *root = Clay__LayoutElementTreeRootArray_Get(&Clay__layoutElementTreeRoots, rootIndex);
        Clay__int32_tArray_Add(&dfsBuffer, (int32_t)root->layoutElementIndex);
        Clay__treeNodeVisited.internalArray[0] = false;
        if (rootIndex > 0) {
            CLAY(CLAY_IDI("Clay__DebugView_EmptyRowOuter", rootIndex), CLAY_LAYOUT({ .sizing = {.width = CLAY_SIZING_GROW({})}, .padding = {CLAY__DEBUGVIEW_INDENT_WIDTH / 2} })) {
                CLAY(CLAY_IDI("Clay__DebugView_EmptyRow", rootIndex), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW({}), .height = CLAY_SIZING_FIXED((float)CLAY__DEBUGVIEW_ROW_HEIGHT) }}), CLAY_BORDER({ .top = { .width = 1, .color = CLAY__DEBUGVIEW_COLOR_3 } })) {}
            }
            layoutData.rowCount++;
        }
        while (dfsBuffer.length > 0) {
            uint32_t currentElementIndex = Clay__int32_tArray_Get(&dfsBuffer, (int)dfsBuffer.length - 1);
            Clay_LayoutElement *currentElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, (int)currentElementIndex);
            if (Clay__treeNodeVisited.internalArray[dfsBuffer.length - 1]) {
                if (!Clay__ElementHasConfig(currentElement, CLAY__ELEMENT_CONFIG_TYPE_TEXT) && currentElement->children.length > 0) {
                    Clay__CloseElement();
                    Clay__CloseElement();
                    Clay__CloseElement();
                }
                dfsBuffer.length--;
                continue;
            }

            if (highlightedRowIndex == layoutData.rowCount) {
                if (Clay__pointerInfo.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
                    Clay__debugSelectedElementId = currentElement->id;
                }
                highlightedElementId = currentElement->id;
            }

            Clay__treeNodeVisited.internalArray[dfsBuffer.length - 1] = true;
            Clay_LayoutElementHashMapItem *currentElementData = Clay__GetHashMapItem(currentElement->id);
            Clay_BoundingBox currentElementBoundingBox = currentElementData->boundingBox;
            #ifndef CLAY_DISABLE_CULLING
                bool offscreen = currentElementBoundingBox.x > (float)Clay__layoutDimensions.width || currentElementBoundingBox.y > (float)Clay__layoutDimensions.height || currentElementBoundingBox.x + currentElementBoundingBox.width < 0 || currentElementBoundingBox.y + currentElementBoundingBox.height < 0;
            #elif
                bool offscreen = false;
            #endif
            if (Clay__debugSelectedElementId == currentElement->id) {
                layoutData.selectedElementRowIndex = layoutData.rowCount;
            }
            CLAY(CLAY_IDI("Clay__DebugView_ElementOuter", currentElement->id), Clay__AttachLayoutConfig(&Clay__DebugView_ScrollViewItemLayoutConfig)) {
                // Collapse icon / button
                if (!(Clay__ElementHasConfig(currentElement, CLAY__ELEMENT_CONFIG_TYPE_TEXT) || currentElement->children.length == 0)) {
                    CLAY(CLAY_IDI("Clay__DebugView_CollapseElement", currentElement->id),
                        CLAY_LAYOUT({ .sizing = {CLAY_SIZING_FIXED(16), CLAY_SIZING_FIXED(16)}, .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER} }),
                        CLAY_BORDER_OUTSIDE_RADIUS(1, CLAY__DEBUGVIEW_COLOR_3, 4)
                    ) {
                        CLAY_TEXT((currentElementData && currentElementData->debugData->collapsed) ? CLAY_STRING("+") : CLAY_STRING("-"), CLAY_TEXT_CONFIG({ .textColor = CLAY__DEBUGVIEW_COLOR_4, .fontSize = 16 }));
                    }
                } else { // Square dot for empty containers
                    CLAY(CLAY_LAYOUT({ .sizing = {CLAY_SIZING_FIXED(16), CLAY_SIZING_FIXED(16)}, .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER } })) {
                        CLAY(CLAY_LAYOUT({ .sizing = {CLAY_SIZING_FIXED(8), CLAY_SIZING_FIXED(8)} }), CLAY_RECTANGLE({ .color = CLAY__DEBUGVIEW_COLOR_3, .cornerRadius = CLAY_CORNER_RADIUS(2) })) {}
                    }
                }
                // Collisions and offscreen info
                if (currentElementData) {
                    if (currentElementData->debugData->collision) {
                        CLAY(CLAY_LAYOUT({ .padding = { 8, 2 } }), CLAY_BORDER_OUTSIDE_RADIUS(1, (CLAY__INIT(Clay_Color){177, 147, 8, 255}), 4)) {
                            CLAY_TEXT(CLAY_STRING("Duplicate ID"), CLAY_TEXT_CONFIG({ .textColor = CLAY__DEBUGVIEW_COLOR_3, .fontSize = 16 }));
                        }
                    }
                    if (offscreen) {
                        CLAY(CLAY_LAYOUT({ .padding = { 8, 2 } }), CLAY_BORDER_OUTSIDE_RADIUS(1, CLAY__DEBUGVIEW_COLOR_3, 4)) {
                            CLAY_TEXT(CLAY_STRING("Offscreen"), CLAY_TEXT_CONFIG({ .textColor = CLAY__DEBUGVIEW_COLOR_3, .fontSize = 16 }));
                        }
                    }
                }
                Clay_String idString = Clay__layoutElementIdStrings.internalArray[currentElementIndex];
                if (idString.length > 0) {
                    CLAY_TEXT(idString, offscreen ? CLAY_TEXT_CONFIG({ .textColor = CLAY__DEBUGVIEW_COLOR_3, .fontSize = 16 }) : &Clay__DebugView_TextNameConfig);
                }
                for (int elementConfigIndex = 0; elementConfigIndex < currentElement->elementConfigs.length; ++elementConfigIndex) {
                    Clay_ElementConfig *elementConfig = Clay__ElementConfigArraySlice_Get(&currentElement->elementConfigs, elementConfigIndex);
                    Clay__DebugElementConfigTypeLabelConfig config = Clay__DebugGetElementConfigTypeLabel(elementConfig->type);
                    Clay_Color backgroundColor = config.color;
                    backgroundColor.a = 90;
                    CLAY(CLAY_LAYOUT({ .padding = { 8, 2 } }), CLAY_RECTANGLE({ .color = backgroundColor, .cornerRadius = CLAY_CORNER_RADIUS(4) }), CLAY_BORDER_OUTSIDE_RADIUS(1, config.color, 4)) {
                        CLAY_TEXT(config.label, CLAY_TEXT_CONFIG({ .textColor = offscreen ? CLAY__DEBUGVIEW_COLOR_3 : CLAY__DEBUGVIEW_COLOR_4, .fontSize = 16 }));
                    }
                }
            }

            // Render the text contents below the element as a non-interactive row
            if (Clay__ElementHasConfig(currentElement, CLAY__ELEMENT_CONFIG_TYPE_TEXT)) {
                layoutData.rowCount++;
                Clay__TextElementData *textElementData = currentElement->textElementData;
                Clay_TextElementConfig *rawTextConfig = offscreen ? CLAY_TEXT_CONFIG({ .textColor = CLAY__DEBUGVIEW_COLOR_3, .fontSize = 16 }) : &Clay__DebugView_TextNameConfig;
                CLAY(CLAY_LAYOUT({ .sizing = { .height = CLAY_SIZING_FIXED(CLAY__DEBUGVIEW_ROW_HEIGHT)}, .childAlignment = { .y = CLAY_ALIGN_Y_CENTER } }), CLAY_RECTANGLE({})) {
                    CLAY(CLAY_LAYOUT({ .sizing = {CLAY_SIZING_FIXED(CLAY__DEBUGVIEW_INDENT_WIDTH + 16)} })) {}
                    CLAY_TEXT(CLAY_STRING("\""), rawTextConfig);
                    CLAY_TEXT(textElementData->text.length > 40 ? (CLAY__INIT(Clay_String) { .length = 40, .chars = textElementData->text.chars }) : textElementData->text, rawTextConfig);
                    if (textElementData->text.length > 40) {
                        CLAY_TEXT(CLAY_STRING("..."), rawTextConfig);
                    }
                    CLAY_TEXT(CLAY_STRING("\""), rawTextConfig);
                }
            } else if (currentElement->children.length > 0) {
                Clay__OpenElement();
                CLAY_LAYOUT({ .padding = { 8 } });
                Clay__ElementPostConfiguration();
                Clay__OpenElement();
                CLAY_BORDER({ .left = { .width = 1, .color = CLAY__DEBUGVIEW_COLOR_3 }});
                Clay__ElementPostConfiguration();
                CLAY(CLAY_LAYOUT({ .sizing = {CLAY_SIZING_FIXED( CLAY__DEBUGVIEW_INDENT_WIDTH)}, .childAlignment = { .x = CLAY_ALIGN_X_RIGHT } })) {}
                Clay__OpenElement();
                CLAY_LAYOUT({ .layoutDirection = CLAY_TOP_TO_BOTTOM });
                Clay__ElementPostConfiguration();
            }

            layoutData.rowCount++;
            if (!(Clay__ElementHasConfig(currentElement, CLAY__ELEMENT_CONFIG_TYPE_TEXT) || (currentElementData && currentElementData->debugData->collapsed))) {
                for (int i = currentElement->children.length - 1; i >= 0; --i) {
                    Clay__int32_tArray_Add(&dfsBuffer, currentElement->children.elements[i]);
                    Clay__treeNodeVisited.internalArray[dfsBuffer.length - 1] = false; // TODO needs to be ranged checked
                }
            }
        }
    }

    if (Clay__pointerInfo.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        Clay_ElementId collapseButtonId = Clay__HashString(CLAY_STRING("Clay__DebugView_CollapseElement"), 0, 0);
        if (Clay__pointerInfo.position.x > Clay__layoutDimensions.width - (float)Clay__debugViewWidth && Clay__pointerInfo.position.x < Clay__layoutDimensions.width && Clay__pointerInfo.position.y > 0 && Clay__pointerInfo.position.y < Clay__layoutDimensions.height) {
            for (int i = (int)Clay__pointerOverIds.length - 1; i >= 0; i--) {
                Clay_ElementId *elementId = Clay__ElementIdArray_Get(&Clay__pointerOverIds, i);
                if (elementId->baseId == collapseButtonId.baseId) {
                    Clay_LayoutElementHashMapItem *highlightedItem = Clay__GetHashMapItem(elementId->offset);
                    highlightedItem->debugData->collapsed = !highlightedItem->debugData->collapsed;
                    break;
                }
            }
        }
    }

    if (highlightedElementId) {
        CLAY(CLAY_ID("Clay__DebugView_ElementHighlight"), CLAY_LAYOUT({ .sizing = {CLAY_SIZING_GROW({}), CLAY_SIZING_GROW({})} }), CLAY_FLOATING({ .zIndex = 65535, .parentId = highlightedElementId })) {
            CLAY(CLAY_ID("Clay__DebugView_ElementHighlightRectangle"), CLAY_LAYOUT({ .sizing = {CLAY_SIZING_GROW({}), CLAY_SIZING_GROW({})} }), CLAY_RECTANGLE({.color = Clay__debugViewHighlightColor })) {}
        }
    }
    return layoutData;
}

void Clay__RenderDebugLayoutSizing(Clay_SizingAxis sizing, Clay_TextElementConfig *infoTextConfig) {
    Clay_String sizingLabel = CLAY_STRING("GROW");
    if (sizing.type == CLAY__SIZING_TYPE_FIT) {
        sizingLabel = CLAY_STRING("FIT");
    } else if (sizing.type == CLAY__SIZING_TYPE_PERCENT) {
        sizingLabel = CLAY_STRING("PERCENT");
    }
    CLAY_TEXT(sizingLabel, infoTextConfig);
    if (sizing.type == CLAY__SIZING_TYPE_GROW || sizing.type == CLAY__SIZING_TYPE_FIT) {
        CLAY_TEXT(CLAY_STRING("("), infoTextConfig);
        if (sizing.sizeMinMax.min != 0) {
            CLAY_TEXT(CLAY_STRING("min: "), infoTextConfig);
            CLAY_TEXT(Clay__IntToString(sizing.sizeMinMax.min), infoTextConfig);
            if (sizing.sizeMinMax.max != CLAY__MAXFLOAT) {
                CLAY_TEXT(CLAY_STRING(", "), infoTextConfig);
            }
        }
        if (sizing.sizeMinMax.max != CLAY__MAXFLOAT) {
            CLAY_TEXT(CLAY_STRING("max: "), infoTextConfig);
            CLAY_TEXT(Clay__IntToString(sizing.sizeMinMax.max), infoTextConfig);
        }
        CLAY_TEXT(CLAY_STRING(")"), infoTextConfig);
    }
}

void Clay__RenderDebugViewElementConfigHeader(Clay_String elementId, Clay__ElementConfigType type) {
    Clay__DebugElementConfigTypeLabelConfig config = Clay__DebugGetElementConfigTypeLabel(type);
    Clay_Color backgroundColor = config.color;
    backgroundColor.a = 90;
    CLAY(CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW({}), CLAY_SIZING_FIXED(CLAY__DEBUGVIEW_ROW_HEIGHT + 8)}, .padding = {CLAY__DEBUGVIEW_OUTER_PADDING }, .childAlignment = { .y = CLAY_ALIGN_Y_CENTER } })) {
        CLAY(CLAY_LAYOUT({ .padding = { 8, 2 } }), CLAY_RECTANGLE({ .color = backgroundColor, .cornerRadius = CLAY_CORNER_RADIUS(4) }), CLAY_BORDER_OUTSIDE_RADIUS(1, config.color, 4)) {
            CLAY_TEXT(config.label, CLAY_TEXT_CONFIG({ .textColor = CLAY__DEBUGVIEW_COLOR_4, .fontSize = 16 }));
        }
        CLAY(CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW({}) } })) {}
        CLAY_TEXT(elementId, CLAY_TEXT_CONFIG({ .textColor = CLAY__DEBUGVIEW_COLOR_3, .fontSize = 16, .wrapMode = CLAY_TEXT_WRAP_NONE }));
    }
}

void Clay__RenderDebugViewColor(Clay_Color color, Clay_TextElementConfig *textConfig) {
    CLAY(CLAY_LAYOUT({ .childAlignment = {.y = CLAY_ALIGN_Y_CENTER} })) {
        CLAY_TEXT(CLAY_STRING("{ r: "), textConfig);
        CLAY_TEXT(Clay__IntToString(color.r), textConfig);
        CLAY_TEXT(CLAY_STRING(", g: "), textConfig);
        CLAY_TEXT(Clay__IntToString(color.g), textConfig);
        CLAY_TEXT(CLAY_STRING(", b: "), textConfig);
        CLAY_TEXT(Clay__IntToString(color.b), textConfig);
        CLAY_TEXT(CLAY_STRING(", a: "), textConfig);
        CLAY_TEXT(Clay__IntToString(color.a), textConfig);
        CLAY_TEXT(CLAY_STRING(" }"), textConfig);
        CLAY(CLAY_LAYOUT({ .sizing = {CLAY_SIZING_FIXED(10) } })) {}
        CLAY(CLAY_LAYOUT({ .sizing = { CLAY_SIZING_FIXED(CLAY__DEBUGVIEW_ROW_HEIGHT - 8), CLAY_SIZING_FIXED(CLAY__DEBUGVIEW_ROW_HEIGHT - 8)} }), CLAY_BORDER_OUTSIDE_RADIUS(1, CLAY__DEBUGVIEW_COLOR_4, 4)) {
            CLAY(CLAY_LAYOUT({ .sizing = { CLAY_SIZING_FIXED(CLAY__DEBUGVIEW_ROW_HEIGHT - 8), CLAY_SIZING_FIXED(CLAY__DEBUGVIEW_ROW_HEIGHT - 8)} }), CLAY_RECTANGLE({ .color = color, .cornerRadius = CLAY_CORNER_RADIUS(4) })) {}
        }
    }
}

void Clay__RenderDebugViewCornerRadius(Clay_CornerRadius cornerRadius, Clay_TextElementConfig *textConfig) {
    CLAY(CLAY_LAYOUT({ .childAlignment = {.y = CLAY_ALIGN_Y_CENTER} })) {
        CLAY_TEXT(CLAY_STRING("{ topLeft: "), textConfig);
        CLAY_TEXT(Clay__IntToString(cornerRadius.topLeft), textConfig);
        CLAY_TEXT(CLAY_STRING(", topRight: "), textConfig);
        CLAY_TEXT(Clay__IntToString(cornerRadius.topRight), textConfig);
        CLAY_TEXT(CLAY_STRING(", bottomLeft: "), textConfig);
        CLAY_TEXT(Clay__IntToString(cornerRadius.bottomLeft), textConfig);
        CLAY_TEXT(CLAY_STRING(", bottomRight: "), textConfig);
        CLAY_TEXT(Clay__IntToString(cornerRadius.bottomRight), textConfig);
        CLAY_TEXT(CLAY_STRING(" }"), textConfig);
    }
}

void Clay__RenderDebugViewBorder(int index, Clay_Border border, Clay_TextElementConfig *textConfig) {
    CLAY(CLAY_LAYOUT({ .childAlignment = {.y = CLAY_ALIGN_Y_CENTER} })) {
        CLAY_TEXT(CLAY_STRING("{ width: "), textConfig);
        CLAY_TEXT(Clay__IntToString(border.width), textConfig);
        CLAY_TEXT(CLAY_STRING(", color: "), textConfig);
        Clay__RenderDebugViewColor(border.color, textConfig);
        CLAY_TEXT(CLAY_STRING(" }"), textConfig);
    }
}

void HandleDebugViewCloseButtonInteraction(Clay_ElementId elementId, Clay_PointerData pointerInfo, intptr_t userData) {
    if (pointerInfo.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        Clay__debugModeEnabled = false;
    }
}

void Clay__RenderDebugView() {
    Clay_ElementId closeButtonId = Clay__HashString(CLAY_STRING("Clay__DebugViewTopHeaderCloseButtonOuter"), 0, 0);
    if (Clay__pointerInfo.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        for (int i = 0; i < Clay__pointerOverIds.length; ++i) {
            Clay_ElementId *elementId = Clay__ElementIdArray_Get(&Clay__pointerOverIds, i);
            if (elementId->id == closeButtonId.id) {
                Clay__debugModeEnabled = false;
                return;
            }
        }
    }

    uint32_t initialRootsLength = Clay__layoutElementTreeRoots.length;
    uint32_t initialElementsLength = Clay__layoutElements.length;
    Clay_TextElementConfig *infoTextConfig = CLAY_TEXT_CONFIG({ .textColor = CLAY__DEBUGVIEW_COLOR_4, .fontSize = 16, .wrapMode = CLAY_TEXT_WRAP_NONE });
    Clay_TextElementConfig *infoTitleConfig = CLAY_TEXT_CONFIG({ .textColor = CLAY__DEBUGVIEW_COLOR_3, .fontSize = 16, .wrapMode = CLAY_TEXT_WRAP_NONE });
    Clay_ElementId scrollId = Clay__HashString(CLAY_STRING("Clay__DebugViewOuterScrollPane"), 0, 0);
    float scrollYOffset = 0;
    for (int i = 0; i < Clay__scrollContainerDatas.length; ++i) {
        Clay__ScrollContainerDataInternal *scrollContainerData = Clay__ScrollContainerDataInternalArray_Get(&Clay__scrollContainerDatas, i);
        if (scrollContainerData->elementId == scrollId.id) {
            scrollYOffset = scrollContainerData->scrollPosition.y;
            break;
        }
    }
    int32_t highlightedRow = (int32_t)((Clay__pointerInfo.position.y - scrollYOffset) / (float)CLAY__DEBUGVIEW_ROW_HEIGHT) - 1;
    if (Clay__pointerInfo.position.x < Clay__layoutDimensions.width - (float)Clay__debugViewWidth) {
        highlightedRow = -1;
    }
    Clay__RenderDebugLayoutData layoutData = {};
    CLAY(CLAY_ID("Clay__DebugView"),
        CLAY_FLOATING({ .parentId = Clay__HashString(CLAY_STRING("Clay__RootContainer"), 0, 0).id, .attachment = { .element = CLAY_ATTACH_POINT_LEFT_CENTER, .parent = CLAY_ATTACH_POINT_RIGHT_CENTER }}),
        CLAY_LAYOUT({ .sizing = { CLAY_SIZING_FIXED((float)Clay__debugViewWidth) , CLAY_SIZING_FIXED(Clay__layoutDimensions.height) }, .layoutDirection = CLAY_TOP_TO_BOTTOM }),
        CLAY_BORDER({ .bottom = { .width = 1, .color = CLAY__DEBUGVIEW_COLOR_3 }})
    ) {
        CLAY(CLAY_LAYOUT({ .sizing = {CLAY_SIZING_GROW({}), CLAY_SIZING_FIXED(CLAY__DEBUGVIEW_ROW_HEIGHT)}, .padding = {CLAY__DEBUGVIEW_OUTER_PADDING}, .childAlignment = {.y = CLAY_ALIGN_Y_CENTER} }), CLAY_RECTANGLE({ .color = CLAY__DEBUGVIEW_COLOR_2 })) {
            CLAY_TEXT(CLAY_STRING("Clay Debug Tools"), infoTextConfig);
            CLAY(CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW({}) } })) {}
            // Close button
            CLAY(CLAY_BORDER_OUTSIDE_RADIUS(1, (CLAY__INIT(Clay_Color){217,91,67,255}), 4),
                CLAY_LAYOUT({ .sizing = {CLAY_SIZING_FIXED(CLAY__DEBUGVIEW_ROW_HEIGHT - 10), CLAY_SIZING_FIXED(CLAY__DEBUGVIEW_ROW_HEIGHT - 10)}, .childAlignment = {CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER} }),
                CLAY_RECTANGLE({ .color = {217,91,67,80} }),
                Clay_OnHover(HandleDebugViewCloseButtonInteraction, 0)
            ) {
                CLAY_TEXT(CLAY_STRING("x"), CLAY_TEXT_CONFIG({ .textColor = CLAY__DEBUGVIEW_COLOR_4, .fontSize = 16 }));
            }
        }
        CLAY(CLAY_LAYOUT({ .sizing = {CLAY_SIZING_GROW({}), CLAY_SIZING_FIXED(1)} }), CLAY_RECTANGLE({ .color = CLAY__DEBUGVIEW_COLOR_3 })) {}
        CLAY(Clay__AttachId(scrollId), CLAY_LAYOUT({ .sizing = {CLAY_SIZING_GROW({}), CLAY_SIZING_GROW({})} }), CLAY_SCROLL({ .horizontal = true, .vertical = true })) {
            CLAY(CLAY_LAYOUT({ .sizing = {CLAY_SIZING_GROW({}), CLAY_SIZING_GROW({})}, .layoutDirection = CLAY_TOP_TO_BOTTOM }), CLAY_RECTANGLE({ .color = ((initialElementsLength + initialRootsLength) & 1) == 0 ? CLAY__DEBUGVIEW_COLOR_2 : CLAY__DEBUGVIEW_COLOR_1 })) {
                Clay_ElementId panelContentsId = Clay__HashString(CLAY_STRING("Clay__DebugViewPaneOuter"), 0, 0);
                // Element list
                CLAY(Clay__AttachId(panelContentsId), CLAY_LAYOUT({ .sizing = {CLAY_SIZING_GROW({}), CLAY_SIZING_GROW({})} }), CLAY_FLOATING({})) {
                    CLAY(CLAY_LAYOUT({ .sizing = {CLAY_SIZING_GROW({}), CLAY_SIZING_GROW({})}, .padding = {.x = CLAY__DEBUGVIEW_OUTER_PADDING }, .layoutDirection = CLAY_TOP_TO_BOTTOM })) {
                        layoutData = Clay__RenderDebugLayoutElementsList((int32_t)initialRootsLength, highlightedRow);
                    }
                }
                float contentWidth = Clay__GetHashMapItem(panelContentsId.id)->layoutElement->dimensions.width;
                CLAY(CLAY_LAYOUT({ .sizing = {CLAY_SIZING_FIXED(contentWidth)}, .layoutDirection = CLAY_TOP_TO_BOTTOM })) {}
                for (uint32_t i = 0; i < layoutData.rowCount; i++) {
                    Clay_Color rowColor = (i & 1) == 0 ? CLAY__DEBUGVIEW_COLOR_2 : CLAY__DEBUGVIEW_COLOR_1;
                    if (i == layoutData.selectedElementRowIndex) {
                        rowColor = CLAY__DEBUGVIEW_COLOR_SELECTED_ROW;
                    }
                    if (i == highlightedRow) {
                        rowColor.r *= 1.25f;
                        rowColor.g *= 1.25f;
                        rowColor.b *= 1.25f;
                    }
                    CLAY(CLAY_LAYOUT({ .sizing = {CLAY_SIZING_GROW({}), CLAY_SIZING_FIXED(CLAY__DEBUGVIEW_ROW_HEIGHT)}, .layoutDirection = CLAY_TOP_TO_BOTTOM }), CLAY_RECTANGLE({ .color = rowColor })) {}
                }
            }
        }
        CLAY(CLAY_LAYOUT({ .sizing = {.width = CLAY_SIZING_GROW({}), .height = CLAY_SIZING_FIXED(1)} }), CLAY_RECTANGLE({ .color = CLAY__DEBUGVIEW_COLOR_3 })) {}
        if (Clay__debugSelectedElementId != 0) {
            Clay_LayoutElementHashMapItem *selectedItem = Clay__GetHashMapItem(Clay__debugSelectedElementId);
            CLAY(
                CLAY_SCROLL({ .vertical = true }),
                CLAY_LAYOUT({ .sizing = {CLAY_SIZING_GROW({}), CLAY_SIZING_FIXED(300)}, .layoutDirection = CLAY_TOP_TO_BOTTOM }),
                CLAY_RECTANGLE({ .color = CLAY__DEBUGVIEW_COLOR_2 }),
                CLAY_BORDER({ .betweenChildren = { .width = 1, .color = CLAY__DEBUGVIEW_COLOR_3 }})
            ) {
                CLAY(CLAY_LAYOUT({ .sizing = {CLAY_SIZING_GROW({}), CLAY_SIZING_FIXED(CLAY__DEBUGVIEW_ROW_HEIGHT + 8)}, .padding = {CLAY__DEBUGVIEW_OUTER_PADDING}, .childAlignment = {.y = CLAY_ALIGN_Y_CENTER} })) {
                    CLAY_TEXT(CLAY_STRING("Layout Config"), infoTextConfig);
                    CLAY(CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW({}) } })) {}
                    if (selectedItem->elementId.stringId.length != 0) {
                        CLAY_TEXT(selectedItem->elementId.stringId, infoTitleConfig);
                        if (selectedItem->elementId.offset != 0) {
                            CLAY_TEXT(CLAY_STRING(" ("), infoTitleConfig);
                            CLAY_TEXT(Clay__IntToString(selectedItem->elementId.offset), infoTitleConfig);
                            CLAY_TEXT(CLAY_STRING(")"), infoTitleConfig);
                        }
                    }
                }
                // Clay_LayoutConfig debug info
                CLAY(CLAY_LAYOUT({ .padding = {CLAY__DEBUGVIEW_OUTER_PADDING, 8}, .childGap = 8, .layoutDirection = CLAY_TOP_TO_BOTTOM })) {
                    // .boundingBox
                    CLAY_TEXT(CLAY_STRING("Bounding Box"), infoTitleConfig);
                    CLAY(CLAY_LAYOUT({})) {
                        CLAY_TEXT(CLAY_STRING("{ x: "), infoTextConfig);
                        CLAY_TEXT(Clay__IntToString(selectedItem->boundingBox.x), infoTextConfig);
                        CLAY_TEXT(CLAY_STRING(", y: "), infoTextConfig);
                        CLAY_TEXT(Clay__IntToString(selectedItem->boundingBox.y), infoTextConfig);
                        CLAY_TEXT(CLAY_STRING(", width: "), infoTextConfig);
                        CLAY_TEXT(Clay__IntToString(selectedItem->boundingBox.width), infoTextConfig);
                        CLAY_TEXT(CLAY_STRING(", height: "), infoTextConfig);
                        CLAY_TEXT(Clay__IntToString(selectedItem->boundingBox.height), infoTextConfig);
                        CLAY_TEXT(CLAY_STRING(" }"), infoTextConfig);
                    }
                    // .layoutDirection
                    CLAY_TEXT(CLAY_STRING("Layout Direction"), infoTitleConfig);
                    Clay_LayoutConfig *layoutConfig = selectedItem->layoutElement->layoutConfig;
                    CLAY_TEXT(layoutConfig->layoutDirection == CLAY_TOP_TO_BOTTOM ? CLAY_STRING("TOP_TO_BOTTOM") : CLAY_STRING("LEFT_TO_RIGHT"), infoTextConfig);
                    // .sizing
                    CLAY_TEXT(CLAY_STRING("Sizing"), infoTitleConfig);
                    CLAY(CLAY_LAYOUT({})) {
                        CLAY_TEXT(CLAY_STRING("width: "), infoTextConfig);
                        Clay__RenderDebugLayoutSizing(layoutConfig->sizing.width, infoTextConfig);
                    }
                    CLAY(CLAY_LAYOUT({})) {
                        CLAY_TEXT(CLAY_STRING("height: "), infoTextConfig);
                        Clay__RenderDebugLayoutSizing(layoutConfig->sizing.height, infoTextConfig);
                    }
                    // .padding
                    CLAY_TEXT(CLAY_STRING("Padding"), infoTitleConfig);
                    CLAY(CLAY_ID("Clay__DebugViewElementInfoPadding")) {
                        CLAY_TEXT(CLAY_STRING("{ x: "), infoTextConfig);
                        CLAY_TEXT(Clay__IntToString(layoutConfig->padding.x), infoTextConfig);
                        CLAY_TEXT(CLAY_STRING(", y: "), infoTextConfig);
                        CLAY_TEXT(Clay__IntToString(layoutConfig->padding.y), infoTextConfig);
                        CLAY_TEXT(CLAY_STRING(" }"), infoTextConfig);
                    }
                    // .childGap
                    CLAY_TEXT(CLAY_STRING("Child Gap"), infoTitleConfig);
                    CLAY_TEXT(Clay__IntToString(layoutConfig->childGap), infoTextConfig);
                    // .childAlignment
                    CLAY_TEXT(CLAY_STRING("Child Alignment"), infoTitleConfig);
                    CLAY(CLAY_LAYOUT({})) {
                        CLAY_TEXT(CLAY_STRING("{ x: "), infoTextConfig);
                        Clay_String alignX = CLAY_STRING("LEFT");
                        if (layoutConfig->childAlignment.x == CLAY_ALIGN_X_CENTER) {
                            alignX = CLAY_STRING("CENTER");
                        } else if (layoutConfig->childAlignment.x == CLAY_ALIGN_X_RIGHT) {
                            alignX = CLAY_STRING("RIGHT");
                        }
                        CLAY_TEXT(alignX, infoTextConfig);
                        CLAY_TEXT(CLAY_STRING(", y: "), infoTextConfig);
                        Clay_String alignY = CLAY_STRING("TOP");
                        if (layoutConfig->childAlignment.y == CLAY_ALIGN_Y_CENTER) {
                            alignY = CLAY_STRING("CENTER");
                        } else if (layoutConfig->childAlignment.y == CLAY_ALIGN_Y_BOTTOM) {
                            alignY = CLAY_STRING("BOTTOM");
                        }
                        CLAY_TEXT(alignY, infoTextConfig);
                        CLAY_TEXT(CLAY_STRING(" }"), infoTextConfig);
                    }
                }
                for (int elementConfigIndex = 0; elementConfigIndex < selectedItem->layoutElement->elementConfigs.length; ++elementConfigIndex) {
                    Clay_ElementConfig *elementConfig = Clay__ElementConfigArraySlice_Get(&selectedItem->layoutElement->elementConfigs, elementConfigIndex);
                    Clay__RenderDebugViewElementConfigHeader(selectedItem->elementId.stringId, elementConfig->type);
                    switch (elementConfig->type) {
                        case CLAY__ELEMENT_CONFIG_TYPE_RECTANGLE: {
                            Clay_RectangleElementConfig *rectangleConfig = elementConfig->config.rectangleElementConfig;
                            CLAY(CLAY_LAYOUT({ .padding = {CLAY__DEBUGVIEW_OUTER_PADDING, 8}, .childGap = 8, .layoutDirection = CLAY_TOP_TO_BOTTOM })) {
                                // .color
                                CLAY_TEXT(CLAY_STRING("Color"), infoTitleConfig);
                                Clay__RenderDebugViewColor(rectangleConfig->color, infoTextConfig);
                                // .cornerRadius
                                CLAY_TEXT(CLAY_STRING("Corner Radius"), infoTitleConfig);
                                Clay__RenderDebugViewCornerRadius(rectangleConfig->cornerRadius, infoTextConfig);
                            }
                            break;
                        }
                        case CLAY__ELEMENT_CONFIG_TYPE_TEXT: {
                            Clay_TextElementConfig *textConfig = elementConfig->config.textElementConfig;
                            CLAY(CLAY_LAYOUT({ .padding = {CLAY__DEBUGVIEW_OUTER_PADDING, 8}, .childGap = 8, .layoutDirection = CLAY_TOP_TO_BOTTOM })) {
                                // .fontSize
                                CLAY_TEXT(CLAY_STRING("Font Size"), infoTitleConfig);
                                CLAY_TEXT(Clay__IntToString(textConfig->fontSize), infoTextConfig);
                                // .fontId
                                CLAY_TEXT(CLAY_STRING("Font ID"), infoTitleConfig);
                                CLAY_TEXT(Clay__IntToString(textConfig->fontId), infoTextConfig);
                                // .lineHeight
                                CLAY_TEXT(CLAY_STRING("Line Height"), infoTitleConfig);
                                CLAY_TEXT(textConfig->lineHeight == 0 ? CLAY_STRING("auto") : Clay__IntToString(textConfig->lineHeight), infoTextConfig);
                                // .letterSpacing
                                CLAY_TEXT(CLAY_STRING("Letter Spacing"), infoTitleConfig);
                                CLAY_TEXT(Clay__IntToString(textConfig->letterSpacing), infoTextConfig);
                                // .lineSpacing
                                CLAY_TEXT(CLAY_STRING("Wrap Mode"), infoTitleConfig);
                                Clay_String wrapMode = CLAY_STRING("WORDS");
                                if (textConfig->wrapMode == CLAY_TEXT_WRAP_NONE) {
                                    wrapMode = CLAY_STRING("NONE");
                                } else if (textConfig->wrapMode == CLAY_TEXT_WRAP_NEWLINES) {
                                    wrapMode = CLAY_STRING("NEWLINES");
                                }
                                CLAY_TEXT(wrapMode, infoTextConfig);
                                // .textColor
                                CLAY_TEXT(CLAY_STRING("Text Color"), infoTitleConfig);
                                Clay__RenderDebugViewColor(textConfig->textColor, infoTextConfig);
                            }
                            break;
                        }
                        case CLAY__ELEMENT_CONFIG_TYPE_IMAGE: {
                            Clay_ImageElementConfig *imageConfig = elementConfig->config.imageElementConfig;
                            CLAY(CLAY_ID("Clay__DebugViewElementInfoImageBody"), CLAY_LAYOUT({ .padding = {CLAY__DEBUGVIEW_OUTER_PADDING, 8}, .childGap = 8, .layoutDirection = CLAY_TOP_TO_BOTTOM })) {
                                // .sourceDimensions
                                CLAY_TEXT(CLAY_STRING("Source Dimensions"), infoTitleConfig);
                                CLAY(CLAY_ID("Clay__DebugViewElementInfoImageDimensions")) {
                                    CLAY_TEXT(CLAY_STRING("{ width: "), infoTextConfig);
                                    CLAY_TEXT(Clay__IntToString(imageConfig->sourceDimensions.width), infoTextConfig);
                                    CLAY_TEXT(CLAY_STRING(", height: "), infoTextConfig);
                                    CLAY_TEXT(Clay__IntToString(imageConfig->sourceDimensions.height), infoTextConfig);
                                    CLAY_TEXT(CLAY_STRING(" }"), infoTextConfig);
                                }
                                // Image Preview
                                CLAY_TEXT(CLAY_STRING("Preview"), infoTitleConfig);
                                CLAY(CLAY_LAYOUT({ .sizing = { CLAY_SIZING_GROW({ .max = imageConfig->sourceDimensions.width }) }}), Clay__AttachElementConfig(CLAY__INIT(Clay_ElementConfigUnion) { .imageElementConfig = imageConfig }, CLAY__ELEMENT_CONFIG_TYPE_IMAGE)) {}
                            }
                            break;
                        }
                        case CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER: {
                            Clay_ScrollElementConfig *scrollConfig = elementConfig->config.scrollElementConfig;
                            CLAY(CLAY_LAYOUT({ .padding = {CLAY__DEBUGVIEW_OUTER_PADDING, 8}, .childGap = 8, .layoutDirection = CLAY_TOP_TO_BOTTOM })) {
                                // .vertical
                                CLAY_TEXT(CLAY_STRING("Vertical"), infoTitleConfig);
                                CLAY_TEXT(scrollConfig->vertical ? CLAY_STRING("true") : CLAY_STRING("false") , infoTextConfig);
                                // .horizontal
                                CLAY_TEXT(CLAY_STRING("Horizontal"), infoTitleConfig);
                                CLAY_TEXT(scrollConfig->horizontal ? CLAY_STRING("true") : CLAY_STRING("false") , infoTextConfig);
                            }
                            break;
                        }
                        case CLAY__ELEMENT_CONFIG_TYPE_FLOATING_CONTAINER: {
                            Clay_FloatingElementConfig *floatingConfig = elementConfig->config.floatingElementConfig;
                            CLAY(CLAY_LAYOUT({ .padding = {CLAY__DEBUGVIEW_OUTER_PADDING, 8}, .childGap = 8, .layoutDirection = CLAY_TOP_TO_BOTTOM })) {
                                // .offset
                                CLAY_TEXT(CLAY_STRING("Offset"), infoTitleConfig);
                                CLAY(CLAY_LAYOUT({})) {
                                    CLAY_TEXT(CLAY_STRING("{ x: "), infoTextConfig);
                                    CLAY_TEXT(Clay__IntToString(floatingConfig->offset.x), infoTextConfig);
                                    CLAY_TEXT(CLAY_STRING(", y: "), infoTextConfig);
                                    CLAY_TEXT(Clay__IntToString(floatingConfig->offset.y), infoTextConfig);
                                    CLAY_TEXT(CLAY_STRING(" }"), infoTextConfig);
                                }
                                // .expand
                                CLAY_TEXT(CLAY_STRING("Expand"), infoTitleConfig);
                                CLAY(CLAY_LAYOUT({})) {
                                    CLAY_TEXT(CLAY_STRING("{ width: "), infoTextConfig);
                                    CLAY_TEXT(Clay__IntToString(floatingConfig->expand.width), infoTextConfig);
                                    CLAY_TEXT(CLAY_STRING(", height: "), infoTextConfig);
                                    CLAY_TEXT(Clay__IntToString(floatingConfig->expand.height), infoTextConfig);
                                    CLAY_TEXT(CLAY_STRING(" }"), infoTextConfig);
                                }
                                // .zIndex
                                CLAY_TEXT(CLAY_STRING("z-index"), infoTitleConfig);
                                CLAY_TEXT(Clay__IntToString(floatingConfig->zIndex), infoTextConfig);
                                // .parentId
                                CLAY_TEXT(CLAY_STRING("Parent"), infoTitleConfig);
                                Clay_LayoutElementHashMapItem *hashItem = Clay__GetHashMapItem(floatingConfig->parentId);
                                CLAY_TEXT(hashItem->elementId.stringId, infoTextConfig);
                            }
                            break;
                        }
                        case CLAY__ELEMENT_CONFIG_TYPE_BORDER_CONTAINER: {
                            Clay_BorderElementConfig *borderConfig = elementConfig->config.borderElementConfig;
                            CLAY(CLAY_ID("Clay__DebugViewElementInfoBorderBody"), CLAY_LAYOUT({ .padding = {CLAY__DEBUGVIEW_OUTER_PADDING, 8}, .childGap = 8, .layoutDirection = CLAY_TOP_TO_BOTTOM })) {
                                // .left
                                CLAY_TEXT(CLAY_STRING("Left Border"), infoTitleConfig);
                                Clay__RenderDebugViewBorder(1, borderConfig->left, infoTextConfig);
                                // .right
                                CLAY_TEXT(CLAY_STRING("Right Border"), infoTitleConfig);
                                Clay__RenderDebugViewBorder(2, borderConfig->right, infoTextConfig);
                                // .top
                                CLAY_TEXT(CLAY_STRING("Top Border"), infoTitleConfig);
                                Clay__RenderDebugViewBorder(3, borderConfig->top, infoTextConfig);
                                // .bottom
                                CLAY_TEXT(CLAY_STRING("Bottom Border"), infoTitleConfig);
                                Clay__RenderDebugViewBorder(4, borderConfig->bottom, infoTextConfig);
                                // .betweenChildren
                                CLAY_TEXT(CLAY_STRING("Border Between Children"), infoTitleConfig);
                                Clay__RenderDebugViewBorder(5, borderConfig->betweenChildren, infoTextConfig);
                                // .cornerRadius
                                CLAY_TEXT(CLAY_STRING("Corner Radius"), infoTitleConfig);
                                Clay__RenderDebugViewCornerRadius(borderConfig->cornerRadius, infoTextConfig);
                            }
                            break;
                        }
                        case CLAY__ELEMENT_CONFIG_TYPE_CUSTOM: {
                            break;
                        }
                    }
                }
            }
        } else {
            CLAY(CLAY_ID("Clay__DebugViewWarningsScrollPane"), CLAY_LAYOUT({ .sizing = {CLAY_SIZING_GROW({}), CLAY_SIZING_FIXED(300)}, .childGap = 6, .layoutDirection = CLAY_TOP_TO_BOTTOM }), CLAY_SCROLL({ .horizontal = true, .vertical = true }), CLAY_RECTANGLE({ .color = CLAY__DEBUGVIEW_COLOR_2 })) {
                Clay_TextElementConfig *warningConfig = CLAY_TEXT_CONFIG({ .textColor = CLAY__DEBUGVIEW_COLOR_4, .fontSize = 16, .wrapMode = CLAY_TEXT_WRAP_NONE });
                CLAY(CLAY_ID("Clay__DebugViewWarningItemHeader"), CLAY_LAYOUT({ .sizing = {.height = CLAY_SIZING_FIXED(CLAY__DEBUGVIEW_ROW_HEIGHT)}, .padding = {CLAY__DEBUGVIEW_OUTER_PADDING}, .childGap = 8, .childAlignment = {.y = CLAY_ALIGN_Y_CENTER} })) {
                    CLAY_TEXT(CLAY_STRING("Warnings"), warningConfig);
                }
                CLAY(CLAY_ID("Clay__DebugViewWarningsTopBorder"), CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW({}), .height = CLAY_SIZING_FIXED(1)} }), CLAY_RECTANGLE({ .color = {200, 200, 200, 255} })) {}
                int previousWarningsLength = (int)Clay_warnings.length;
                for (int i = 0; i < previousWarningsLength; i++) {
                    Clay__Warning warning = Clay_warnings.internalArray[i];
                    CLAY(CLAY_IDI("Clay__DebugViewWarningItem", i), CLAY_LAYOUT({ .sizing = {.height = CLAY_SIZING_FIXED(CLAY__DEBUGVIEW_ROW_HEIGHT)}, .padding = {CLAY__DEBUGVIEW_OUTER_PADDING}, .childGap = 8, .childAlignment = {.y = CLAY_ALIGN_Y_CENTER} })) {
                        CLAY_TEXT(warning.baseMessage, warningConfig);
                        if (warning.dynamicMessage.length > 0) {
                            CLAY_TEXT(warning.dynamicMessage, warningConfig);
                        }
                    }
                }
            }
        }
    }
}
#pragma endregion

// PUBLIC API FROM HERE ---------------------------------------

CLAY_WASM_EXPORT("Clay_MinMemorySize")
uint32_t Clay_MinMemorySize() {
    Clay_Arena fakeArena = CLAY__INIT(Clay_Arena) { .capacity = INT64_MAX };
    Clay__InitializePersistentMemory(&fakeArena);
    Clay__InitializeEphemeralMemory(&fakeArena);
    return fakeArena.nextAllocation;
}

CLAY_WASM_EXPORT("Clay_CreateArenaWithCapacityAndMemory")
Clay_Arena Clay_CreateArenaWithCapacityAndMemory(uint32_t capacity, void *offset) {
    Clay_Arena arena = CLAY__INIT(Clay_Arena) {
        .capacity = capacity,
        .memory = (char *)offset
    };
    return arena;
}

#ifndef CLAY_WASM
void Clay_SetMeasureTextFunction(Clay_Dimensions (*measureTextFunction)(Clay_String *text, Clay_TextElementConfig *config)) {
    Clay__MeasureText = measureTextFunction;
}
#endif

CLAY_WASM_EXPORT("Clay_SetLayoutDimensions")
void Clay_SetLayoutDimensions(Clay_Dimensions dimensions) {
    Clay__layoutDimensions = dimensions;
}

CLAY_WASM_EXPORT("Clay_SetPointerState")
void Clay_SetPointerState(Clay_Vector2 position, bool isPointerDown) {
    Clay__pointerInfo.position = position;
    Clay__pointerOverIds.length = 0;
    Clay__int32_tArray dfsBuffer = Clay__layoutElementChildrenBuffer;
    for (int rootIndex = 0; rootIndex < Clay__layoutElementTreeRoots.length; ++rootIndex) {
        dfsBuffer.length = 0;
        Clay__LayoutElementTreeRoot *root = Clay__LayoutElementTreeRootArray_Get(&Clay__layoutElementTreeRoots, rootIndex);
        Clay__int32_tArray_Add(&dfsBuffer, (int32_t)root->layoutElementIndex);
        Clay__treeNodeVisited.internalArray[0] = false;
        while (dfsBuffer.length > 0) {
            if (Clay__treeNodeVisited.internalArray[dfsBuffer.length - 1]) {
                dfsBuffer.length--;
                continue;
            }
            Clay__treeNodeVisited.internalArray[dfsBuffer.length - 1] = true;
            Clay_LayoutElement *currentElement = Clay_LayoutElementArray_Get(&Clay__layoutElements, Clay__int32_tArray_Get(&dfsBuffer, (int)dfsBuffer.length - 1));
            Clay_LayoutElementHashMapItem *mapItem = Clay__GetHashMapItem(currentElement->id); // TODO think of a way around this, maybe the fact that it's essentially a binary tree limits the cost, but the worst case is not great
            if (mapItem && Clay__PointIsInsideRect(position, mapItem->boundingBox)) {
                if (mapItem->onHoverFunction) {
                    mapItem->onHoverFunction(mapItem->elementId, Clay__pointerInfo, mapItem->hoverFunctionUserData);
                }
                Clay__ElementIdArray_Add(&Clay__pointerOverIds, mapItem->elementId);
                if (Clay__ElementHasConfig(currentElement, CLAY__ELEMENT_CONFIG_TYPE_TEXT)) {
                    dfsBuffer.length--;
                    continue;
                }
                for (int i = currentElement->children.length - 1; i >= 0; --i) {
                    Clay__int32_tArray_Add(&dfsBuffer, currentElement->children.elements[i]);
                    Clay__treeNodeVisited.internalArray[dfsBuffer.length - 1] = false; // TODO needs to be ranged checked
                }
            } else {
                dfsBuffer.length--;
            }
        }
    }

    if (isPointerDown) {
        if (Clay__pointerInfo.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
            Clay__pointerInfo.state = CLAY_POINTER_DATA_PRESSED;
        } else if (Clay__pointerInfo.state != CLAY_POINTER_DATA_PRESSED) {
            Clay__pointerInfo.state = CLAY_POINTER_DATA_PRESSED_THIS_FRAME;
        }
    } else {
        if (Clay__pointerInfo.state == CLAY_POINTER_DATA_RELEASED_THIS_FRAME) {
            Clay__pointerInfo.state = CLAY_POINTER_DATA_RELEASED;
        } else if (Clay__pointerInfo.state != CLAY_POINTER_DATA_RELEASED)  {
            Clay__pointerInfo.state = CLAY_POINTER_DATA_RELEASED_THIS_FRAME;
        }
    }
}

CLAY_WASM_EXPORT("Clay_Initialize")
void Clay_Initialize(Clay_Arena arena, Clay_Dimensions layoutDimensions) {
    Clay__internalArena = arena;
    Clay__InitializePersistentMemory(&Clay__internalArena);
    Clay__InitializeEphemeralMemory(&Clay__internalArena);
    for (int i = 0; i < Clay__layoutElementsHashMap.capacity; ++i) {
        Clay__layoutElementsHashMap.internalArray[i] = -1;
    }
    for (int i = 0; i < Clay__measureTextHashMap.capacity; ++i) {
        Clay__measureTextHashMap.internalArray[i] = 0;
    }
    Clay__measureTextHashMapInternal.length = 1; // Reserve the 0 value to mean "no next element"
    Clay__layoutDimensions = layoutDimensions;
}

CLAY_WASM_EXPORT("Clay_UpdateScrollContainers")
void Clay_UpdateScrollContainers(bool enableDragScrolling, Clay_Vector2 scrollDelta, float deltaTime) {
    bool isPointerActive = enableDragScrolling && (Clay__pointerInfo.state == CLAY_POINTER_DATA_PRESSED || Clay__pointerInfo.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME);
    // Don't apply scroll events to ancestors of the inner element
    int32_t highestPriorityElementIndex = -1;
    Clay__ScrollContainerDataInternal *highestPriorityScrollData = CLAY__NULL;
    for (int i = 0; i < Clay__scrollContainerDatas.length; i++) {
        Clay__ScrollContainerDataInternal *scrollData = Clay__ScrollContainerDataInternalArray_Get(&Clay__scrollContainerDatas, i);
        if (!scrollData->openThisFrame) {
            Clay__ScrollContainerDataInternalArray_RemoveSwapback(&Clay__scrollContainerDatas, i);
            continue;
        }
        scrollData->openThisFrame = false;
        Clay_LayoutElementHashMapItem *hashMapItem = Clay__GetHashMapItem(scrollData->elementId);
        // Element isn't rendered this frame but scroll offset has been retained
        if (!hashMapItem) {
            Clay__ScrollContainerDataInternalArray_RemoveSwapback(&Clay__scrollContainerDatas, i);
            continue;
        }

        // Touch / click is released
        if (!isPointerActive && scrollData->pointerScrollActive) {
            float xDiff = scrollData->scrollPosition.x - scrollData->scrollOrigin.x;
            if (xDiff < -10 || xDiff > 10) {
                scrollData->scrollMomentum.x = (scrollData->scrollPosition.x - scrollData->scrollOrigin.x) / (scrollData->momentumTime * 25);
            }
            float yDiff = scrollData->scrollPosition.y - scrollData->scrollOrigin.y;
            if (yDiff < -10 || yDiff > 10) {
                scrollData->scrollMomentum.y = (scrollData->scrollPosition.y - scrollData->scrollOrigin.y) / (scrollData->momentumTime * 25);
            }
            scrollData->pointerScrollActive = false;

            scrollData->pointerOrigin = CLAY__INIT(Clay_Vector2){0,0};
            scrollData->scrollOrigin = CLAY__INIT(Clay_Vector2){0,0};
            scrollData->momentumTime = 0;
        }

        // Apply existing momentum
        scrollData->scrollPosition.x += scrollData->scrollMomentum.x;
        scrollData->scrollMomentum.x *= 0.95f;
        bool scrollOccurred = scrollDelta.x != 0 || scrollDelta.y != 0;
        if ((scrollData->scrollMomentum.x > -0.1f && scrollData->scrollMomentum.x < 0.1f) || scrollOccurred) {
            scrollData->scrollMomentum.x = 0;
        }
        scrollData->scrollPosition.x = CLAY__MIN(CLAY__MAX(scrollData->scrollPosition.x, -(CLAY__MAX(scrollData->contentSize.width - scrollData->layoutElement->dimensions.width, 0))), 0);

        scrollData->scrollPosition.y += scrollData->scrollMomentum.y;
        scrollData->scrollMomentum.y *= 0.95f;
        if ((scrollData->scrollMomentum.y > -0.1f && scrollData->scrollMomentum.y < 0.1f) || scrollOccurred) {
            scrollData->scrollMomentum.y = 0;
        }
        scrollData->scrollPosition.y = CLAY__MIN(CLAY__MAX(scrollData->scrollPosition.y, -(CLAY__MAX(scrollData->contentSize.height - scrollData->layoutElement->dimensions.height, 0))), 0);

        for (int j = 0; j < Clay__pointerOverIds.length; ++j) { // TODO n & m are small here but this being n*m gives me the creeps
            if (scrollData->layoutElement->id == Clay__ElementIdArray_Get(&Clay__pointerOverIds, j)->id) {
                highestPriorityElementIndex = j;
                highestPriorityScrollData = scrollData;
            }
        }
    }

    if (highestPriorityElementIndex > -1 && highestPriorityScrollData) {
        Clay_LayoutElement *scrollElement = highestPriorityScrollData->layoutElement;
        Clay_ScrollElementConfig *scrollConfig = Clay__FindElementConfigWithType(scrollElement, CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER).scrollElementConfig;
        bool canScrollVertically = scrollConfig->vertical && highestPriorityScrollData->contentSize.height > scrollElement->dimensions.height;
        bool canScrollHorizontally = scrollConfig->horizontal && highestPriorityScrollData->contentSize.width > scrollElement->dimensions.width;
        // Handle wheel scroll
        if (canScrollVertically) {
            highestPriorityScrollData->scrollPosition.y = highestPriorityScrollData->scrollPosition.y + scrollDelta.y * 10;
        }
        if (canScrollHorizontally) {
            highestPriorityScrollData->scrollPosition.x = highestPriorityScrollData->scrollPosition.x + scrollDelta.x * 10;
        }
        // Handle click / touch scroll
        if (isPointerActive) {
            highestPriorityScrollData->scrollMomentum = CLAY__INIT(Clay_Vector2){0};
            if (!highestPriorityScrollData->pointerScrollActive) {
                highestPriorityScrollData->pointerOrigin = Clay__pointerInfo.position;
                highestPriorityScrollData->scrollOrigin = highestPriorityScrollData->scrollPosition;
                highestPriorityScrollData->pointerScrollActive = true;
            } else {
                float scrollDeltaX = 0, scrollDeltaY = 0;
                if (canScrollHorizontally) {
                    float oldXScrollPosition = highestPriorityScrollData->scrollPosition.x;
                    highestPriorityScrollData->scrollPosition.x = highestPriorityScrollData->scrollOrigin.x + (Clay__pointerInfo.position.x - highestPriorityScrollData->pointerOrigin.x);
                    highestPriorityScrollData->scrollPosition.x = CLAY__MAX(CLAY__MIN(highestPriorityScrollData->scrollPosition.x, 0), -(highestPriorityScrollData->contentSize.width - highestPriorityScrollData->boundingBox.width));
                    scrollDeltaX = highestPriorityScrollData->scrollPosition.x - oldXScrollPosition;
                }
                if (canScrollVertically) {
                    float oldYScrollPosition = highestPriorityScrollData->scrollPosition.y;
                    highestPriorityScrollData->scrollPosition.y = highestPriorityScrollData->scrollOrigin.y + (Clay__pointerInfo.position.y - highestPriorityScrollData->pointerOrigin.y);
                    highestPriorityScrollData->scrollPosition.y = CLAY__MAX(CLAY__MIN(highestPriorityScrollData->scrollPosition.y, 0), -(highestPriorityScrollData->contentSize.height - highestPriorityScrollData->boundingBox.height));
                    scrollDeltaY = highestPriorityScrollData->scrollPosition.y - oldYScrollPosition;
                }
                if (scrollDeltaX > -0.1f && scrollDeltaX < 0.1f && scrollDeltaY > -0.1f && scrollDeltaY < 0.1f && highestPriorityScrollData->momentumTime > 0.15f) {
                    highestPriorityScrollData->momentumTime = 0;
                    highestPriorityScrollData->pointerOrigin = Clay__pointerInfo.position;
                    highestPriorityScrollData->scrollOrigin = highestPriorityScrollData->scrollPosition;
                } else {
                     highestPriorityScrollData->momentumTime += deltaTime;
                }
            }
        }
        // Clamp any changes to scroll position to the maximum size of the contents
        if (canScrollVertically) {
            highestPriorityScrollData->scrollPosition.y = CLAY__MAX(CLAY__MIN(highestPriorityScrollData->scrollPosition.y, 0), -(highestPriorityScrollData->contentSize.height - scrollElement->dimensions.height));
        }
        if (canScrollHorizontally) {
            highestPriorityScrollData->scrollPosition.x = CLAY__MAX(CLAY__MIN(highestPriorityScrollData->scrollPosition.x, 0), -(highestPriorityScrollData->contentSize.width - scrollElement->dimensions.width));
        }
    }
}

CLAY_WASM_EXPORT("Clay_BeginLayout")
void Clay_BeginLayout() {
    Clay__InitializeEphemeralMemory(&Clay__internalArena);
    Clay__generation++;
    Clay__dynamicElementIndex = 0;
    // Set up the root container that covers the entire window
    Clay_Dimensions rootDimensions = CLAY__INIT(Clay_Dimensions) {Clay__layoutDimensions.width, Clay__layoutDimensions.height};
    if (Clay__debugModeEnabled) {
        rootDimensions.width -= (float)Clay__debugViewWidth;
    }
    Clay__OpenElement();
    CLAY_ID("Clay__RootContainer");
    CLAY_LAYOUT({ .sizing = {CLAY_SIZING_FIXED((rootDimensions.width)), CLAY_SIZING_FIXED(rootDimensions.height)} });
    Clay__ElementPostConfiguration();
    Clay__int32_tArray_Add(&Clay__openLayoutElementStack, 0);
    Clay__LayoutElementTreeRootArray_Add(&Clay__layoutElementTreeRoots, CLAY__INIT(Clay__LayoutElementTreeRoot) { .layoutElementIndex = 0 });
}

CLAY_WASM_EXPORT("Clay_EndLayout")
Clay_RenderCommandArray Clay_EndLayout()
{
    Clay__CloseElement();
    if (Clay__debugModeEnabled) {
        #ifndef CLAY_DEBUG
        Clay__warningsEnabled = false;
        #endif
        Clay__RenderDebugView();
        #ifndef CLAY_DEBUG
        Clay__warningsEnabled = true;
        #endif
    }
    Clay__CalculateFinalLayout();
    return Clay__renderCommands;
}

CLAY_WASM_EXPORT("Clay_GetElementId")
Clay_ElementId Clay_GetElementId(Clay_String idString) {
    return Clay__HashString(idString, 0, 0);
}

CLAY_WASM_EXPORT("Clay_GetElementIdWithIndex")
Clay_ElementId Clay_GetElementIdWithIndex(Clay_String idString, uint32_t index) {
    return Clay__HashString(idString, index, 0);
}

bool Clay_Hovered() {
    Clay_LayoutElement *openLayoutElement = Clay__GetOpenLayoutElement();
    // If the element has no id attached at this point, we need to generate one
    if (openLayoutElement->id == 0) {
        Clay__GenerateIdForAnonymousElement(openLayoutElement);
    }
    for (int i = 0; i < Clay__pointerOverIds.length; ++i) {
        if (Clay__ElementIdArray_Get(&Clay__pointerOverIds, i)->id == openLayoutElement->id) {
            return true;
        }
    }
    return false;
}

void Clay_OnHover(void (*onHoverFunction)(Clay_ElementId elementId, Clay_PointerData pointerInfo, intptr_t userData), intptr_t userData) {
    Clay_LayoutElement *openLayoutElement = Clay__GetOpenLayoutElement();
    if (openLayoutElement->id == 0) {
        Clay__GenerateIdForAnonymousElement(openLayoutElement);
    }
    Clay_LayoutElementHashMapItem *hashMapItem = Clay__GetHashMapItem(openLayoutElement->id);
    hashMapItem->onHoverFunction = onHoverFunction;
    hashMapItem->hoverFunctionUserData = userData;
}

CLAY_WASM_EXPORT("Clay_PointerOver")
bool Clay_PointerOver(Clay_ElementId elementId) { // TODO return priority for separating multiple results
    for (int i = 0; i < Clay__pointerOverIds.length; ++i) {
        if (Clay__ElementIdArray_Get(&Clay__pointerOverIds, i)->id == elementId.id) {
            return true;
        }
    }
    return false;
}

CLAY_WASM_EXPORT("Clay_GetScrollContainerData")
Clay_ScrollContainerData Clay_GetScrollContainerData(Clay_ElementId id) {
    for (int i = 0; i < Clay__scrollContainerDatas.length; ++i) {
        Clay__ScrollContainerDataInternal *scrollContainerData = Clay__ScrollContainerDataInternalArray_Get(&Clay__scrollContainerDatas, i);
        if (scrollContainerData->elementId == id.id) {
            return CLAY__INIT(Clay_ScrollContainerData) {
                .scrollPosition = &scrollContainerData->scrollPosition,
                .scrollContainerDimensions = CLAY__INIT(Clay_Dimensions) { scrollContainerData->boundingBox.width, scrollContainerData->boundingBox.height },
                .contentDimensions = scrollContainerData->contentSize,
                .config = *Clay__FindElementConfigWithType(scrollContainerData->layoutElement, CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER).scrollElementConfig,
                .found = true
            };
        }
    }
    return CLAY__INIT(Clay_ScrollContainerData) {};
}

CLAY_WASM_EXPORT("Clay_SetDebugModeEnabled")
void Clay_SetDebugModeEnabled(bool enabled) {
    Clay__debugModeEnabled = enabled;
}

#endif //CLAY_IMPLEMENTATION

/*
LICENSE
zlib/libpng license

Copyright (c) 2024 Nic Barker

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the
use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software in a
    product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not
    be misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.
*/
