namespace liminal {

struct WindowProperties {
    const int width;
    const int height;
    const char* title;
    const int fontSize;

    WindowProperties(const int w, const int h, const char* t, const int fs) : width(w), height(h), title(t), fontSize(fs) {}
};

} // namespace liminal