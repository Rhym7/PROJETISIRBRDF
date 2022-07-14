#ifndef __RT_ISICG_BRDF_ORENNAYAR__
#define __RT_ISICG_BRDF_ORENNAYAR__

#include "defines.hpp"

namespace RT_ISICG
{
	class OrenNayarBRDF
	{
	  public:
		OrenNayarBRDF( const Vec3f & p_kd, float p_sigma ) : _kd( p_kd ), sigma_pente(p_sigma) {};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate(const Vec3f & _wo, const Vec3f & _wi, const Vec3f & _n) const {

			// Calculs des données nécéssaires
			float costhetaO = glm::dot(_wo, _n );
			float costhetaI = glm::dot( _wi, _n );

			float thetaO = glm::acos( costhetaO );
			float thetaI = glm::acos( costhetaI );

			float aLPHA = glm::max( thetaI, thetaO );
			float bETA	= glm::min( thetaI, thetaO );

			float sigmacarre = sigma_pente * sigma_pente;
			float _A		 = 1.0f - ( ( 0.5f * sigmacarre ) / ( sigmacarre + 0.33f ) );
			float _B		 = ( 0.45f * sigmacarre ) / ( sigmacarre + 0.09f );

			Vec3f phiO = (_wo - _n * costhetaO);
			Vec3f phiI = ( _wi - _n  *costhetaI);

			float cosphiIminusphiO = glm::dot( phiI, phiO );
			
			// Calcul de la BRDF
			Vec3f _BRDF = ( _kd / glm::pi<float>()) * (_A + (cosphiIminusphiO >= 0 ? _B  * cosphiIminusphiO * glm::sin(aLPHA) * glm::tan(bETA) : 0.f));
			
		
			return _BRDF;
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd = WHITE;
		float sigma_pente;
		
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_LAMBERT__#pragma once
