class Solution {
public:
    double angleClock(int hour, int minutes) {
        double hangle = 30*hour + 0.5*minutes;
        double mangle = 6*minutes;

        double diff = abs(hangle - mangle);

        return min(diff, 360-diff);
    }
};