/* -*- c++ -*- */
/*
 * gr-leo: SatNOGS GNU Radio Out-Of-Tree Module
 *
 *  Copyright (C) 2018, Libre Space Foundation <https://libre.space/>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "atmospheric_gases_itu_impl.h"
#include <cmath>
#include <leo/log.h>

namespace gr
{
  namespace leo
  {
    namespace attenuation
    {

      generic_attenuation::generic_attenuation_sptr
      atmospheric_gases_itu::make (float frequency)
      {
        return generic_attenuation::generic_attenuation_sptr (
            new atmospheric_gases_itu_impl (frequency));
      }

      atmospheric_gases_itu_impl::atmospheric_gases_itu_impl (float frequency) :
              generic_attenuation (),
              d_frequency(frequency),
              d_oxygen_pressure(0),
              d_temperature(0),
              d_water_pressure(0),
              d_elevation_angle(0)
      {

      }

      atmospheric_gases_itu_impl::~atmospheric_gases_itu_impl ()
      {
      }

      float
      atmospheric_gases_itu_impl::geopotential_to_geometric (float alt)
      {
        return (6356.766 * alt) / (6356.766 - alt);
      }

      float
      atmospheric_gases_itu_impl::geometric_to_geopotential (float alt)
      {
        return (6356.766 * alt) / (6356.766 + alt);
      }

      double
      atmospheric_gases_itu_impl::get_temperature (float alt)
      {
        float geopotential_alt = geometric_to_geopotential (alt);
        double temperature = 0;
        /**
         * Troposphere
         */
        if (geopotential_alt >= 0 && geopotential_alt <= 11) {
          temperature = 288.15 - 6.5 * geopotential_alt;
        }
        /**
         * Tropopause
         */
        else if (geopotential_alt > 11 && geopotential_alt <= 20) {
          temperature = 216.65;
        }
        /**
         * Stratosphere
         */
        else if (geopotential_alt > 20 && geopotential_alt <= 32) {
          temperature = 216.65 + geopotential_alt - 20;
        }
        /**
         * Stratosphere
         */
        else if (geopotential_alt > 32 && geopotential_alt <= 47) {
          temperature = 228.65 + 2.8 * (geopotential_alt - 32);
        }
        /**
         * Stratopause
         */
        else if (geopotential_alt > 47 && geopotential_alt <= 51) {
          temperature = 270.65;
        }
        /**
         * Mesosphere
         */
        else if (geopotential_alt > 51 && geopotential_alt <= 71) {
          temperature = 270.65 - 2.8 * (geopotential_alt - 51);
        }
        /**
         * Mesosphere
         */
        else if (geopotential_alt > 71 && geopotential_alt <= 84.852) {
          temperature = 270.65 - 2.8 * (geopotential_alt - 51);
        }
        /**
         * Mesopause
         */
        else if (geopotential_alt > 86 && geopotential_alt <= 91) {
          temperature = 186.8673;
        }
        else if (alt > 91) {
          temperature = 263.1905
              - 76.3232
                  * std::pow (1 - std::pow ((alt - 91) / 19.9429, 2), 0.5);
        }
        return temperature;
      }

      double
      atmospheric_gases_itu_impl::get_pressure (float alt)
      {
        float geopotential_alt = geometric_to_geopotential (alt);
        double pressure = 0;
        const double a0 = 95.571899;
        const double a1 = -4.011801;
        const double a2 = 6.424731e-2;
        const double a3 = -4.789660e-4;
        const double a4 = 1.340543e-6;

        /**
         * Troposphere
         */
        if (geopotential_alt >= 0 && geopotential_alt <= 11) {
          pressure = 1013.25
              * std::pow (288.15 / (288.15 - 6.5 * geopotential_alt),
                          -34.1632 / 6.5);
        }
        /**
         * Tropopause
         */
        else if (geopotential_alt > 11 && geopotential_alt <= 20) {
          pressure = 226.3226
              * std::exp (-34.1632 * (geopotential_alt - 11) / 216.65);
        }
        /**
         * Stratosphere
         */
        else if (geopotential_alt > 20 && geopotential_alt <= 32) {
          pressure = 54.74980
              * std::pow (216.65 / (216.65 + geopotential_alt - 20), -34.1632);
        }
        /**
         * Stratosphere
         */
        else if (geopotential_alt > 32 && geopotential_alt <= 47) {
          pressure = 8.680422
              * std::pow (228.65 / (228.65 + 2.8 * (geopotential_alt - 32)),
                          -34.1632 / 2.8);
        }
        /**
         * Stratopause
         */
        else if (geopotential_alt > 47 && geopotential_alt <= 51) {
          pressure = 1.109106
              * std::exp (-34.1632 * (geopotential_alt - 47) / 270.65);
        }
        /**
         * Mesosphere
         */
        else if (geopotential_alt > 51 && geopotential_alt <= 71) {
          pressure = 0.6694167
              * std::pow (270.65 / (270.65 - 2.8 * (geopotential_alt - 51)),
                          -34.1632 / 2.8);
        }
        /**
         * Mesosphere
         */
        else if (geopotential_alt > 71 && geopotential_alt <= 84.852) {
          pressure = 0.03956649
              * std::pow (214.65 / (214.65 - 2 * (geopotential_alt - 71)),
                          -34.1632 / 2);
        }
        /**
         * Mesopause
         */
        else if (geopotential_alt > 86) {
          pressure = std::exp (
              a0 + a1 * geopotential_alt + a2 * std::pow (geopotential_alt, 2)
                  + a3 * std::pow (geopotential_alt, 3)
                  + a4 * std::pow (geopotential_alt, 4));
        }
        return pressure;
      }

      double
      atmospheric_gases_itu_impl::get_water_vapour_pressure (float alt)
      {
        double rh = 7.5 * std::exp (-alt / 2);
        return (rh * get_temperature (alt)) / 216.7;
      }

      float
      atmospheric_gases_itu_impl::S (size_t index, atmo_element_t element)
      {
        float theta = 300 / d_temperature;
        switch (element)
          {
          case OXYGEN:
            return d_table1[index][1] * 1e-7 * d_oxygen_pressure
                * std::pow (theta, 3)
                * std::exp (d_table1[index][2] * (1 - theta));
            break;
          case WATER_VAPOUR:
            return d_table2[index][1] * (1e-1) * d_water_pressure
                * std::pow (theta, 3.5)
                * std::exp (d_table2[index][2] * (1 - theta));
            break;
          default:
            throw std::runtime_error ("Invalid atmosphere element!");
          }
      }

      float
      atmospheric_gases_itu_impl::F (size_t index, atmo_element_t element)
      {
        float theta = 300 / d_temperature;
        float f0;
        double df;
        double delta = 0;
        double result;

        switch (element)
          {
          case OXYGEN:
            f0 = d_table1[index][0];
            df = d_table1[index][3] * (1e-4)
                * (d_oxygen_pressure
                    * std::pow (theta, 0.8 - d_table1[index][4])
                    + 1.1 * d_water_pressure * theta);
            //TODO: Equation 6b
            delta = (1e-4) * (d_table1[index][5] + d_table1[index][6] * theta)
                * (d_oxygen_pressure + d_water_pressure)
                * std::pow (theta, 0.8);
            result = (d_frequency / f0)
                * (((df - delta * (f0 - d_frequency))
                    / (std::pow (f0 - d_frequency, 2) + std::pow (df, 2)))
                    + ((df - delta * (f0 + d_frequency))
                        / (std::pow (f0 + d_frequency, 2) + std::pow (df, 2))));
            break;
          case WATER_VAPOUR:
            f0 = d_table2[index][0];
            df = d_table2[index][3] * 1e-4
                * (d_oxygen_pressure * std::pow (theta, d_table1[index][4])
                    + d_table2[index][5] * d_water_pressure
                        * std::pow (theta, d_table2[index][6]));
            //TODO: Equation 6b
            delta = 0;
            break;
          default:
            throw std::runtime_error ("Invalid atmosphere element!");
          }
        result = (d_frequency / f0)
            * (((df - delta * (f0 - d_frequency))
                / (std::pow (f0 - d_frequency, 2) + std::pow (df, 2)))
                + ((df - delta * (f0 + d_frequency))
                    / (std::pow (f0 + d_frequency, 2) + std::pow (df, 2))));

        return result;
      }

      float
      atmospheric_gases_itu_impl::ND ()
      {
        float theta = 300 / d_temperature;
        float d = (d_oxygen_pressure + d_water_pressure) * std::pow (theta, 0.8)
            * 5.6e-4;
        return d_frequency * d_oxygen_pressure * std::pow (theta, 2)
            * (6.14e-5 / (d * (1 + std::pow (d_frequency / d, 2)))
                + (d_oxygen_pressure * std::pow (theta, 1.5) * 1.4e-12
                    / (1 + (std::pow (d_frequency, 1.5) * 1.9e-5))));
      }

      float
      atmospheric_gases_itu_impl::N (atmo_element_t element)
      {
        float sum = 0;
        switch (element)
          {
          case OXYGEN:
            for (size_t i = 0; i < d_table1.size (); i++) {
              sum = sum + S (i, element) * F (i, element);
            }
            return sum + ND ();
            break;
          case WATER_VAPOUR:
            for (size_t i = 0; i < d_table2.size (); i++) {
              sum = sum + S (i, element) * F (i, element);
            }
            return sum;
            break;
          default:
            throw std::runtime_error ("Invalid atmosphere element!");
          }

      }

      float
      atmospheric_gases_itu_impl::gamma ()
      {
        return 0.1820 * d_frequency * (N (OXYGEN) + N (WATER_VAPOUR));
      }

      float
      atmospheric_gases_itu_impl::nh (float temperature, float oxygen_pressure,
                                      float watevapour_pressure)
      {
        return 1
            + (77.6 * (oxygen_pressure / temperature)
                + 72 * (watevapour_pressure / temperature)
                + (watevapour_pressure / std::pow (temperature, 2)) * 3.75e5)
                * 1e-6;
      }

      float
      atmospheric_gases_itu_impl::a (float an, float rn, float delta)
      {
        double internal = (-std::pow (an, 2) - 2 * rn * delta
            - std::pow (delta, 2)) / (2 * an * rn + 2 * an * delta);
        if (internal < -1) {
          internal = -1;
        }
        else if (internal > 1) {
          internal = 1;
        }
        float a_tmp = MATH_PI - acos (internal);
        return a_tmp;
      }

      float
      atmospheric_gases_itu_impl::alpha (size_t n, float rn, float delta,
                                         float prev_alpha)
      {
        float b = beta (n, rn, delta, prev_alpha);
        float alpha_tmp = -rn * cos (b)
            + 0.5
                * std::sqrt (
                    4 * std::pow (rn, 2) * std::pow (cos (b), 2)
                        + (8 * rn * delta) + (4 * std::pow (delta, 2)));
        return alpha_tmp;
      }

      float
      atmospheric_gases_itu_impl::beta (size_t n, float rn, float delta,
                                        float prev_alpha)
      {
        float delta_next = 0.0001 * std::exp (((n + 1) - 1) / 100);
        float aangle;
        float bangle;
        if (n == 1) {
          bangle = 1.5707963268 - d_elevation_angle;
          return bangle;
        }
        else {
          aangle = a (prev_alpha, rn, delta);
          bangle = asin (
              (nh (d_temperature, d_oxygen_pressure, d_water_pressure)
                  / nh (
                      get_temperature (rn + delta_next - EARTH_RADIUS),
                      get_pressure (rn + delta_next - EARTH_RADIUS),
                      get_water_vapour_pressure (
                          rn + delta_next - EARTH_RADIUS))) * sin (aangle));
          return bangle;
        }

      }

      float
      atmospheric_gases_itu_impl::get_attenuation(float elevation)
      {
        float delta;
        float delta_sum = 0;
        float attenuation_sum = 0;
        float attenuation;
        float rn = EARTH_RADIUS;
        float prev_alpha = 0;
        float alpha_sum = 0;

        d_elevation_angle = elevation;

        if (d_elevation_angle < 0.0174533) {
          return 0;
        }

        for (size_t i = 1; i <= 922; i++) {
          delta = 0.0001 * std::exp ((i - 1) / 100.0);
          delta_sum += delta;
          rn += delta;
          d_temperature = get_temperature (delta_sum);
          d_oxygen_pressure = get_pressure (delta_sum);
          d_water_pressure = get_water_vapour_pressure (delta_sum);
          prev_alpha = alpha (i, rn, delta, prev_alpha);
          if (!std::isnan (prev_alpha)) {
            alpha_sum += prev_alpha;
          }
          attenuation = prev_alpha * gamma ();
          if (!std::isnan (attenuation)) {
            attenuation_sum += attenuation;
          }
        }

        return attenuation_sum;
      }

    } /* namespace attenuation */
  } /* namespace leo */
} /* namespace gr */

