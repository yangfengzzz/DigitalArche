//  Copyright (c) 2022 Feng Yang
//
//  I am making my contributions/submissions to this project solely in my
//  personal capacity and am not conveying any rights to any intellectual
//  property of any third parties.

#ifndef region_hpp
#define region_hpp

#include "point3.h"
#include "random.h"

namespace vox {
namespace geo {
/**
 * Represents a part of a Volume.
 *
 * Many operations in PolyVox are constrained to only part of a volume. For example, when running the surface extractors
 * it is unlikely that you will want to run it on the whole volume at once, as this will give a very large mesh which may
 * be too much to render. Instead you will probably want to run a surface extractor a number of times on different parts
 * of the volume, there by giving a number of meshes which can be culled and rendered separately.
 *
 * The Region class is used to define these parts (regions) of the volume. Essentially it consists of an upper and lower
 * bound which specify the range of voxels positions considered to be part of the region. Note that these bounds are
 * <em>inclusive</em>.
 *
 * As well as the expected set of getters and setters, this class also provide utility functions for increasing and decreasing
 * the size of the Region, shifting the Region in 3D space, testing whether it contains a given position, enlarging it so that
 * it does contain a given position, cropping it to another Region, and various other utility functions.
 *
 * @note The dimensions of a region can be measured either in voxels or in cells. See the manual for more information
 * about these definitions.
 */
class Region {
public:
    constexpr Region();
    Region(const Point3I& mins, const Point3I& maxs);
    Region(ssize_t minsx, ssize_t minsy, ssize_t minsz, ssize_t maxsx, ssize_t maxsy, ssize_t maxsz);
    Region(ssize_t mins, ssize_t maxs);
    
    static const Region InvalidRegion;
    
    bool operator==(const Region& rhs) const;
    bool operator!=(const Region& rhs) const;
    
    /** Moves the Region by the amount specified. */
    Region& operator+=(const Point3I& amount);
    
    /** Gets the 'x' position of the centre. */
    ssize_t getCenterX() const;
    /** Gets the 'y' position of the centre. */
    ssize_t getCenterY() const;
    /** Gets the 'z' position of the centre. */
    ssize_t getCenterZ() const;
    /** Gets the 'x' position of the lower corner. */
    ssize_t getLowerX() const;
    /** Gets the 'y' position of the lower corner. */
    ssize_t getLowerY() const;
    /** Gets the 'z' position of the lower corner. */
    ssize_t getLowerZ() const;
    /** Gets the 'x' position of the upper corner. */
    ssize_t getUpperX() const;
    /** Gets the 'y' position of the upper corner. */
    ssize_t getUpperY() const;
    /** Gets the 'z' position of the upper corner. */
    ssize_t getUpperZ() const;
    
    /** Gets the centre of the region */
    const Point3I& getCenter() const;
    const Vector3F& getPivot() const;
    /** Gets the position of the lower corner. */
    const Point3I& getLowerCorner() const;
    /** Gets the position of the upper corner. */
    const Point3I& getUpperCorner() const;
    
    Vector3F getLowerCornerf() const;
    Vector3F getUpperCornerf() const;
    
    Point3I getRandomPosition(Random& random) const;
    
    /** Gets the width of the region measured in voxels. */
    ssize_t getWidthInVoxels() const;
    /** Gets the height of the region measured in voxels. */
    ssize_t getHeightInVoxels() const;
    /** Gets the depth of the region measured in voxels. */
    ssize_t getDepthInVoxels() const;
    /** Gets the dimensions of the region measured in voxels. */
    const Point3I& getDimensionsInVoxels() const;
    
    /** Gets the width of the region measured in cells. */
    ssize_t getWidthInCells() const;
    /** Gets the height of the region measured in cells. */
    ssize_t getHeightInCells() const;
    /** Gets the depth of the region measured in cells. */
    ssize_t getDepthInCells() const;
    /** Gets the dimensions of the region measured in cells. */
    const Point3I& getDimensionsInCells() const;
    
    /** Sets the 'x' position of the lower corner. */
    void setLowerX(ssize_t x);
    /** Sets the 'y' position of the lower corner. */
    void setLowerY(ssize_t y0f128);
    /** Sets the 'z' position of the lower corner. */
    void setLowerZ(ssize_t z);
    /** Sets the 'x' position of the upper corner. */
    void setUpperX(ssize_t x);
    /** Sets the 'y' position of the upper corner. */
    void setUpperY(ssize_t y);
    /** Sets the 'z' position of the upper corner. */
    void setUpperZ(ssize_t z);
    
    Point3I moveInto(ssize_t x, ssize_t y, ssize_t z) const;
    
    /** Sets the position of the lower corner. */
    void setLowerCorner(const Point3I& mins);
    /** Sets the position of the upper corner. */
    void setUpperCorner(const Point3I& maxs);
    
    /** Tests whether the given point is contained in this Region. */
    bool containsPoint(float fX, float fY, float fZ, float boundary = 0.0f) const;
    /** Tests whether the given point is contained in this Region. */
    bool containsPoint(const Vector3F& pos, float boundary = 0.0f) const;
    /** Tests whether the given point is contained in this Region. */
    bool containsPoint(ssize_t iX, ssize_t iY, ssize_t iZ, uint8_t boundary = 0) const;
    /** Tests whether the given point is contained in this Region. */
    bool containsPoint(const Point3I& pos, uint8_t boundary = 0) const;
    /** Tests whether the given position is contained in the 'x' range of this Region. */
    bool containsPointInX(float pos, float boundary = 0.0f) const;
    /** Tests whether the given position is contained in the 'x' range of this Region. */
    bool containsPointInX(ssize_t pos, uint8_t boundary = 0) const;
    /** Tests whether the given position is contained in the 'y' range of this Region. */
    bool containsPointInY(float pos, float boundary = 0.0f) const;
    /** Tests whether the given position is contained in the 'y' range of this Region. */
    bool containsPointInY(ssize_t pos, uint8_t boundary = 0) const;
    /** Tests whether the given position is contained in the 'z' range of this Region. */
    bool containsPointInZ(float pos, float boundary = 0.0f) const;
    /** Tests whether the given position is contained in the 'z' range of this Region. */
    bool containsPointInZ(ssize_t pos, uint8_t boundary = 0) const;
    
    /** Tests whether the given Region is contained in this Region. */
    bool containsRegion(const Region& reg, uint8_t boundary = 0) const;
    
    /** Enlarges the Region so that it contains the specified position. */
    void accumulate(ssize_t iX, ssize_t iY, ssize_t iZ);
    /** Enlarges the Region so that it contains the specified position. */
    void accumulate(const Point3I& v3dPos);
    
    /** Enlarges the Region so that it contains the specified Region. */
    void accumulate(const Region& reg);
    
    /** Crops the extents of this Region according to another Region. */
    void cropTo(const Region& other);
    
    /** Grows this region by the amount specified. */
    void grow(ssize_t amount);
    /** Grows this region by the amounts specified. */
    void grow(ssize_t amountX, ssize_t amountY, ssize_t amountZ);
    /** Grows this region by the amounts specified. */
    void grow(const Point3I& v3dAmount);
    
    /** Tests whether all components of the upper corner are at least
     * as great as the corresponding components of the lower corner. */
    bool isValid() const;
    
    /**
     * @return The amount of possible voxels in this region.
     */
    ssize_t voxels() const;
    ssize_t stride() const;
    
    /** Moves the Region by the amount specified. */
    void shift(ssize_t amountX, ssize_t amountY, ssize_t amountZ);
    /** Moves the Region by the amount specified. */
    void shift(const Point3I& v3dAmount);
    /** Moves the lower corner of the Region by the amount specified. */
    void shiftLowerCorner(ssize_t x, ssize_t y, ssize_t z);
    /** Moves the lower corner of the Region by the amount specified. */
    void shiftLowerCorner(const Point3I& v3dAmount);
    /** Moves the upper corner of the Region by the amount specified. */
    void shiftUpperCorner(ssize_t x, ssize_t y, ssize_t z);
    /** Moves the upper corner of the Region by the amount specified. */
    void shiftUpperCorner(const Point3I& v3dAmount);
    
    /** Shrinks this region by the amount specified. */
    void shrink(ssize_t amount);
    /** Shrinks this region by the amounts specified. */
    void shrink(ssize_t amountX, ssize_t amountY, ssize_t amountZ);
    /** Shrinks this region by the amounts specified. */
    void shrink(const Point3I& v3dAmount);
    
    std::string toString(bool center = false) const;
    
private:
    void update();
    
    alignas(16) Point3I _mins;
    alignas(16) Point3I _maxs;
    alignas(16) Point3I _width;
    alignas(16) Point3I _voxels;
    alignas(16) Point3I _center;
    alignas(16) Vector3F _pivot;
    ssize_t _stride;
};

/**
 * @return The 'x' position of the centre.
 */
inline ssize_t Region::getCenterX() const {
    return _center.x;
}

/**
 * @return The 'y' position of the centre.
 */
inline ssize_t Region::getCenterY() const {
    return _center.y;
}

/**
 * @return The 'z' position of the centre.
 */
inline ssize_t Region::getCenterZ() const {
    return _center.z;
}

/**
 * @return The 'x' position of the lower corner.
 */
inline ssize_t Region::getLowerX() const {
    return _mins.x;
}

/**
 * @return The 'y' position of the lower corner.
 */
inline ssize_t Region::getLowerY() const {
    return _mins.y;
}

/**
 * @return The 'z' position of the lower corner.
 */
inline ssize_t Region::getLowerZ() const {
    return _mins.z;
}

/**
 * @return The 'x' position of the upper corner.
 */
inline ssize_t Region::getUpperX() const {
    return _maxs.x;
}

/**
 * @return The 'y' position of the upper corner.
 */
inline ssize_t Region::getUpperY() const {
    return _maxs.y;
}

/**
 * @return The 'z' position of the upper corner.
 */
inline ssize_t Region::getUpperZ() const {
    return _maxs.z;
}

/**
 * @return The width of the region measured in voxels.
 * @sa getWidthInCells()
 */
inline ssize_t Region::getWidthInVoxels() const {
    return _voxels.x;
}

/**
 * @return The height of the region measured in voxels.
 * @sa getHeightInCells()
 */
inline ssize_t Region::getHeightInVoxels() const {
    return _voxels.y;
}

/**
 * @return The depth of the region measured in voxels.
 * @sa getDepthInCells()
 */
inline ssize_t Region::getDepthInVoxels() const {
    return _voxels.z;
}

/**
 * @return The width of the region measured in cells.
 * @sa getWidthInVoxels()
 */
inline ssize_t Region::getWidthInCells() const {
    return _width.x;
}

/**
 * @return The height of the region measured in cells.
 * @sa getHeightInVoxels()
 */
inline ssize_t Region::getHeightInCells() const {
    return _width.y;
}

/**
 * @return The depth of the region measured in cells.
 * @sa getDepthInVoxels()
 */
inline ssize_t Region::getDepthInCells() const {
    return _width.z;
}

inline ssize_t Region::stride() const {
    return _stride;
}

/**
 * @param x The new 'x' position of the lower corner.
 */
inline void Region::setLowerX(ssize_t x) {
    _mins.x = x;
    update();
}

/**
 * @param y The new 'y' position of the lower corner.
 */
inline void Region::setLowerY(ssize_t y) {
    _mins.y = y;
    update();
}

/**
 * @param z The new 'z' position of the lower corner.
 */
inline void Region::setLowerZ(ssize_t z) {
    _mins.z = z;
    update();
}

/**
 * @param x The new 'x' position of the upper corner.
 */
inline void Region::setUpperX(ssize_t x) {
    _maxs.x = x;
    update();
}

/**
 * @param y The new 'y' position of the upper corner.
 */
inline void Region::setUpperY(ssize_t y) {
    _maxs.y = y;
    update();
}

/**
 * @param z The new 'z' position of the upper corner.
 */
inline void Region::setUpperZ(ssize_t z) {
    _maxs.z = z;
    update();
}

inline Region::Region(ssize_t mins, ssize_t maxs) :
Region(mins, mins, mins, maxs, maxs, maxs) {
}

/**
 * Constructs a Region and clears all extents to zero.
 */
inline constexpr Region::Region() :
_mins(0, 0, 0), _maxs(0, 0, 0),
_width(0, 0, 0), _voxels(1, 1, 1), _center(0, 0, 0),
_pivot(0.5f, 0.5f, 0.5f), _stride(0) {
}

/**
 * Constructs a Region and sets the extents to the specified values.
 * @param minsx The desired lower 'x' extent of the Region.
 * @param minsy The desired lower 'y' extent of the Region.
 * @param minsz The desired lower 'z' extent of the Region.
 * @param maxsx The desired upper 'x' extent of the Region.
 * @param maxsy The desired upper 'y' extent of the Region.
 * @param maxsz The desired upper 'z' extent of the Region.
 */
inline Region::Region(ssize_t minsx, ssize_t minsy, ssize_t minsz, ssize_t maxsx, ssize_t maxsy, ssize_t maxsz) :
_mins(minsx, minsy, minsz), _maxs(maxsx, maxsy, maxsz),
_width(_maxs.x - _mins.x, _maxs.y - _mins.y, _maxs.z - _mins.z),
_voxels(_width.x + 1, _width.y + 1, _width.z + 1),
_center(_mins.x + _width.x / 2, _mins.y + _width.y / 2, _mins.z + _width.z / 2),
_pivot(std::floor((float)_voxels.x / 2.0f), std::floor((float)_voxels.y / 2.0f), std::floor((float)_voxels.z / 2.0f)),
_stride(_voxels.x * _voxels.y) {
}

/**
 * Two regions are considered equal if all their extents match.
 * @param rhs The Region to compare to.
 * @return true if the Regions match.
 * @sa operator!=
 */
inline bool Region::operator==(const Region& rhs) const {
    return ((_mins.x == rhs._mins.x) && (_mins.y == rhs._mins.y) && (_mins.z == rhs._mins.z)
            && (_maxs.x == rhs._maxs.x) && (_maxs.y == rhs._maxs.y) && (_maxs.z == rhs._maxs.z));
}

/**
 * Two regions are considered different if any of their extents differ.
 * @param rhs The Region to compare to.
 * @return true if the Regions are different.
 * @sa operator==
 */
inline bool Region::operator!=(const Region& rhs) const {
    return !(*this == rhs);
}

/**
 * The boundary value can be used to ensure a position is only considered to be inside
 * the Region if it is that far in in all directions. Also, the test is inclusive such
 * that positions lying exactly on the edge of the Region are considered to be inside it.
 * @param fX The 'x' position of the point to test.
 * @param fY The 'y' position of the point to test.
 * @param fZ The 'z' position of the point to test.
 * @param boundary The desired boundary value.
 */
inline bool Region::containsPoint(float fX, float fY, float fZ, float boundary) const {
    return (fX <= _maxs.x - boundary) && (fY <= _maxs.y - boundary) && (fZ <= _maxs.z - boundary) && (fX >= _mins.x + boundary) && (fY >= _mins.y + boundary)
    && (fZ >= _mins.z + boundary);
}

/**
 * The boundary value can be used to ensure a position is only considered to be inside
 * the Region if it is that far in in all directions. Also, the test is inclusive such
 * that positions lying exactly on the edge of the Region are considered to be inside it.
 * @param iX The 'x' position of the point to test.
 * @param iY The 'y' position of the point to test.
 * @param iZ The 'z' position of the point to test.
 * @param boundary The desired boundary value.
 */
inline bool Region::containsPoint(ssize_t iX, ssize_t iY, ssize_t iZ, uint8_t boundary) const {
    return (iX <= _maxs.x - boundary) && (iY <= _maxs.y - boundary) && (iZ <= _maxs.z - boundary) && (iX >= _mins.x + boundary) && (iY >= _mins.y + boundary)
    && (iZ >= _mins.z + boundary);
}

/**
 * The boundary value can be used to ensure a position is only considered to be inside
 * the Region if it is that far in in the 'x' direction. Also, the test is inclusive such
 * that positions lying exactly on the edge of the Region are considered to be inside it.
 * @param pos The position to test.
 * @param boundary The desired boundary value.
 */
inline bool Region::containsPointInX(float pos, float boundary) const {
    return (pos <= _maxs.x - boundary) && (pos >= _mins.x + boundary);
}

/**
 * The boundary value can be used to ensure a position is only considered to be inside
 * the Region if it is that far in in the 'x' direction. Also, the test is inclusive such
 * that positions lying exactly on the edge of the Region are considered to be inside it.
 * @param pos The position to test.
 * @param boundary The desired boundary value.
 */
inline bool Region::containsPointInX(ssize_t pos, uint8_t boundary) const {
    return (pos <= _maxs.x - boundary) && (pos >= _mins.x + boundary);
}

/**
 * The boundary value can be used to ensure a position is only considered to be inside
 * the Region if it is that far in in the 'y' direction. Also, the test is inclusive such
 * that positions lying exactly on the edge of the Region are considered to be inside it.
 * @param pos The position to test.
 * @param boundary The desired boundary value.
 */
inline bool Region::containsPointInY(float pos, float boundary) const {
    return (pos <= _maxs.y - boundary) && (pos >= _mins.y + boundary);
}

/**
 * The boundary value can be used to ensure a position is only considered to be inside
 * the Region if it is that far in in the 'y' direction. Also, the test is inclusive such
 * that positions lying exactly on the edge of the Region are considered to be inside it.
 * @param pos The position to test.
 * @param boundary The desired boundary value.
 */
inline bool Region::containsPointInY(ssize_t pos, uint8_t boundary) const {
    return (pos <= _maxs.y - boundary) && (pos >= _mins.y + boundary);
}

/**
 * The boundary value can be used to ensure a position is only considered to be inside
 * the Region if it is that far in in the 'z' direction. Also, the test is inclusive such
 * that positions lying exactly on the edge of the Region are considered to be inside it.
 * @param pos The position to test.
 * @param boundary The desired boundary value.
 */
inline bool Region::containsPointInZ(float pos, float boundary) const {
    return (pos <= _maxs.z - boundary) && (pos >= _mins.z + boundary);
}

/**
 * The boundary value can be used to ensure a position is only considered to be inside
 * the Region if it is that far in in the 'z' direction. Also, the test is inclusive such
 * that positions lying exactly on the edge of the Region are considered to be inside it.
 * @param pos The position to test.
 * @param boundary The desired boundary value.
 */
inline bool Region::containsPointInZ(ssize_t pos, uint8_t boundary) const {
    return (pos <= _maxs.z - boundary) && (pos >= _mins.z + boundary);
}

/**
 * The boundary value can be used to ensure a region is only considered to be inside
 * another Region if it is that far in in all directions. Also, the test is inclusive such
 * that a region is considered to be inside of itself.
 * @param reg The region to test.
 * @param boundary The desired boundary value.
 */
inline bool Region::containsRegion(const Region& reg, uint8_t boundary) const {
    return (reg._maxs.x <= _maxs.x - boundary) && (reg._maxs.y <= _maxs.y - boundary) && (reg._maxs.z <= _maxs.z - boundary)
    && (reg._mins.x >= _mins.x + boundary) && (reg._mins.y >= _mins.y + boundary) && (reg._mins.z >= _mins.z + boundary);
}

inline bool Region::isValid() const {
    return _maxs.x >= _mins.x && _maxs.y >= _mins.y && _maxs.z >= _mins.z;
}

/**
 * @param amountX The amount to move the Region by in 'x'.
 * @param amountY The amount to move the Region by in 'y'.
 * @param amountZ The amount to move the Region by in 'z'.
 */
inline void Region::shift(ssize_t amountX, ssize_t amountY, ssize_t amountZ) {
    shiftLowerCorner(amountX, amountY, amountZ);
    shiftUpperCorner(amountX, amountY, amountZ);
}

/**
 * @param x The amount to move the lower corner by in 'x'.
 * @param y The amount to move the lower corner by in 'y'.
 * @param z The amount to move the lower corner by in 'z'.
 */
inline void Region::shiftLowerCorner(ssize_t x, ssize_t y, ssize_t z) {
    _mins.x += x;
    _mins.y += y;
    _mins.z += z;
    update();
}

/**
 * @param x The amount to move the upper corner by in 'x'.
 * @param y The amount to move the upper corner by in 'y'.
 * @param z The amount to move the upper corner by in 'z'.
 */
inline void Region::shiftUpperCorner(ssize_t x, ssize_t y, ssize_t z) {
    _maxs.x += x;
    _maxs.y += y;
    _maxs.z += z;
    update();
}

/**
 * The same amount of shrinkage is applied in all directions. Negative shrinkage
 * is possible but you should prefer the grow() function for clarity.
 * @param amount The amount to shrink by.
 */
inline void Region::shrink(ssize_t amount) {
    _mins.x += amount;
    _mins.y += amount;
    _mins.z += amount;
    
    _maxs.x -= amount;
    _maxs.y -= amount;
    _maxs.z -= amount;
    update();
}

/**
 * The amount can be specified seperatly for each direction. Negative shrinkage
 * is possible but you should prefer the grow() function for clarity.
 * @param amountX The amount to shrink by in 'x'.
 * @param amountY The amount to shrink by in 'y'.
 * @param amountZ The amount to shrink by in 'z'.
 */
inline void Region::shrink(ssize_t amountX, ssize_t amountY, ssize_t amountZ) {
    _mins.x += amountX;
    _mins.y += amountY;
    _mins.z += amountZ;
    
    _maxs.x -= amountX;
    _maxs.y -= amountY;
    _maxs.z -= amountZ;
    update();
}

/**
 * This function only returns true if the regions are really intersecting and not simply touching.
 */
inline bool intersects(const Region& a, const Region& b) {
    // No intersection if seperated along an axis.
    if (a.getUpperX() < b.getLowerX() || a.getLowerX() > b.getUpperX())
        return false;
    if (a.getUpperY() < b.getLowerY() || a.getLowerY() > b.getUpperY())
        return false;
    if (a.getUpperZ() < b.getLowerZ() || a.getLowerZ() > b.getUpperZ())
        return false;
    
    // Overlapping on all axes means Regions are intersecting.
    return true;
}

extern void logRegion(const char *ctx, const Region& region);


}
}
#endif /* region_hpp */
