#pragma once
#ifndef __RT_ISICG_BRDF_CookTerrance__
#define __RT_ISICG_BRDF_CookTerrance__

#include "defines.hpp"

namespace RT_ISICG
{
	class CookTerrance_brdf
	{
	  public:
		CookTerrance_brdf( const Vec3f & p_kd, const Vec3f & p_F0) : _kd( p_kd ), _F0(p_F0) {};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( const Vec3f & _wo, const Vec3f & _wi, const Vec3f & _n ) const
		{
			Vec3f h = glm::normalize( _wo + _wi );
			float DD = D( h, _n );
			Vec3f FF = F( _wo, h);
			float GG = G( _wi, _wo, _n );

			Vec3f _BRDF = ( DD * FF * GG ) / ( 4 * glm::dot( _wo, _n ) * glm::dot( _wi, _n ) );
			
			return _BRDF;
			
		}

		inline float G1( const float & _X ) const
		{
			float _K = pow(sigma_pente + 1.f, 2.f ) / 8.f;

			float G1;
			G1  = _X / ( _X * ( 1.f - _K ) + _K );

			return G1;
		}

		inline float G( const Vec3f & Wi, const Vec3f & Wo, const Vec3f & _N ) const
		{
			float G = G1( dot( _N, Wo ) ) * G1( dot( _N, Wi ) );
			return G;
		}

        inline Vec3f F( const Vec3f & Wo, const Vec3f & _H ) const
		{
			Vec3f F = _F0 + ( 1.f - _F0 ) * pow( ( 1.f - dot( _H, Wo ) ), 5.f );
			return F;
		}

		inline float D( const Vec3f & _H, const Vec3f & _N ) const
		{
			float aLPHA = sigma_pente * sigma_pente;
			float aLPHACARRE = aLPHA * aLPHA;
			
			float NETHCARRE = pow( glm::dot( _N, _H ), 2.f );
			float calculDENOMINA = glm::pi<float>() * pow( ( NETHCARRE * ( aLPHACARRE - 1.f ) + 1.f ), 2.f );

			float D = aLPHACARRE / calculDENOMINA;
			return D;
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd = WHITE;
		float sigma_pente = 0.3f;
		Vec3f _F0;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_MF__
#pragma once
