#ifndef __RT_ISICG_BRDF_PHONG__
#define __RT_ISICG_BRDF_PHONG__

#include "defines.hpp"

namespace RT_ISICG
{
	class PhongBRDF
	{
	  public:
		PhongBRDF( const Vec3f & p_kd , float _s) : _kd( p_kd ) , _scoef(_s){};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( const Vec3f & _wo, const Vec3f & _wi, const Vec3f & _n ) const
		{
			Vec3f _wr	= glm::reflect(_wi, _n );
			float aLPHA = acos(glm::dot(_wo,_wr));
			
			Vec3f _BRDF = _kd * glm::pow(glm::cos(aLPHA),_scoef) ;
							
			return _BRDF;
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd = WHITE;
		float _scoef;

		
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_PHONG__
#pragma once
