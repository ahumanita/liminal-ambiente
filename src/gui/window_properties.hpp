namespace liminal {

struct WindowProperties {
    int width;
    int height;
    const char* title;

    WindowProperties(int w, int h, const char* t) : width(w), height(h), title(t) {}
};

} // namespace liminal