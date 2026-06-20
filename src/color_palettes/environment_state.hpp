
namespace liminal {

struct EnvironmentState {
    float timeOfDay;        // 0.0 to 1.0, where 0.0 is midnight and 0.5 is noon
    // Future additions are going to include:
    // float cloudCover;       // 0.0 to 1.0, where 0.0 is clear and 1.0 is stormy
    // float rainIntensity;    // 0.0 to 1.0, where 0.0 is no rain and 1.0 is heavy rain
    // float fogDensity;       // 0.0 to 1.0, where 0.0 is clear and 1.0 is dense fog
};

} // namespace liminal