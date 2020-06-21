#ifndef _AddNoise_H__
#define _AddNoise_H__

#include <kvs/PolygonObject>
// #include <pcl/point_cloud.h>
// #include <pcl/kdtree/kdtree_flann.h>
#include <vector>

class AddNoise {

public:
    enum NoiseType {
        Gaussian = 0,
        Poisson  = 1,
        Outlier  = 2
    };

public:
    AddNoise( void );
    AddNoise( double _noise_probability, double _hyperparameter4noise);

    void setNoiseType( NoiseType _type );
    void addNoise( kvs::PolygonObject* _ply );
    std::vector<bool> getIsNoisePoints( void ) { return m_is_noise_points; }

    std::vector<float> getNoiseIntensities( void ) { return m_noise_intensities; }
    double getMaxNoiseIntensity( void ) { return m_max_noise_intensity; }
    double getMinNoiseIntensity( void ) { return m_min_noise_intensity; }
    void normalizeNoiseIntensities( void );

private:
    NoiseType           m_type;
    size_t	            m_number;
    double	            m_sigma;
    double              m_lamda;
    double	            m_noise_probability;
    double              m_hyperparameter4noise;
    std::vector<bool>   m_is_noise_points;

    std::vector<float>  m_noise_intensities;
    double	            m_max_noise_intensity;
    double              m_min_noise_intensity;

private:
    // Gaussian
    void addGaussianNoise( kvs::PolygonObject* _ply );

    // Poisson
    void setLamda( double _ratio4lamda, kvs::Vector3f _bbmin, kvs::Vector3f _bbmax );
    void applyPoissonNoise( kvs::PolygonObject* _ply );

    // Outlier
    void addOutlierNoise( kvs::PolygonObject* _ply );    
};

#endif