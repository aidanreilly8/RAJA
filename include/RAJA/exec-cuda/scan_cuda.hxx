/*!
******************************************************************************
*
* \file
*
* \brief   Header file providing RAJA scan declarations.
*
******************************************************************************
*/

#ifndef RAJA_scan_cuda_HXX
#define RAJA_scan_cuda_HXX

#include "RAJA/config.hxx"

#if defined(RAJA_ENABLE_CUDA)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) 2016, Lawrence Livermore National Security, LLC.
//
// Produced at the Lawrence Livermore National Laboratory
//
// LLNL-CODE-689114
//
// All rights reserved.
//
// This file is part of RAJA.
//
// For additional details, please also read raja/README-license.txt.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the disclaimer below.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the disclaimer (as noted below) in the
//   documentation and/or other materials provided with the distribution.
//
// * Neither the name of the LLNS/LLNL nor the names of its contributors may
//   be used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL SECURITY,
// LLC, THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
// IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#include <thrust/device_ptr.h>
#include <thrust/execution_policy.h>
#include <thrust/functional.h>
#include <thrust/scan.h>

namespace RAJA
{

template <typename InputIter, typename Function, typename T>
void inclusive_scan_inplace(const cuda_exec_base&,
                            InputIter begin,
                            InputIter end,
                            Function binary_op,
                            T init)
{
  ::thrust::inclusive_scan(::thrust::device,
                           ::thrust::device_pointer_cast(begin),
                           ::thrust::device_pointer_cast(end),
                           ::thrust::device_pointer_cast(begin),
                           init,
                           binary_op);
}

template <typename InputIter>
void inclusive_scan_inplace(const cuda_exec_base& exec,
                            InputIter begin,
                            InputIter end)
{
  using Value = typename std::iterator_traits<InputIter>::value_type;
  inclusive_scan_inplace(exec, begin, end, ::thrust::plus<Value>{}, Value{0});
}

template <typename InputIter, typename Function, typename T>
void exclusive_scan_inplace(const cuda_exec_base&,
                            InputIter begin,
                            InputIter end,
                            Function binary_op,
                            T init)
{
  ::thrust::exclusive_scan(::thrust::device,
                           ::thrust::device_pointer_cast(begin),
                           ::thrust::device_pointer_cast(end),
                           ::thrust::device_pointer_cast(begin),
                           init,
                           binary_op);
}

template <typename InputIter>
void exclusive_scan_inplace(const cuda_exec_base& exec,
                            InputIter begin,
                            InputIter end)
{
  using Value = typename std::iterator_traits<InputIter>::value_type;
  exclusive_scan_inplace(exec, begin, end, ::thrust::plus<Value>{}, Value{0});
}

template <typename InputIter,
          typename OutputIter,
          typename Function,
          typename T>
void inclusive_scan_inplace(const cuda_exec_base&,
                            InputIter begin,
                            InputIter end,
                            OutputIter out,
                            Function binary_op,
                            T init)
{
  ::thrust::inclusive_scan(::thrust::device,
                           ::thrust::device_pointer_cast(begin),
                           ::thrust::device_pointer_cast(end),
                           ::thrust::device_pointer_cast(out),
                           init,
                           binary_op);
}

template <typename InputIter, typename OutputIter>
void inclusive_scan_inplace(const cuda_exec_base& exec,
                            InputIter begin,
                            InputIter end,
                            OutputIter out)
{
  using Value = typename std::iterator_traits<InputIter>::value_type;
  inclusive_scan(exec, begin, out, ::thrust::plus<Value>{}, Value{0});
}

template <typename InputIter,
          typename OutputIter,
          typename Function,
          typename T>
void exclusive_scan_inplace(const cuda_exec_base& exec,
                            InputIter begin,
                            InputIter end,
                            OutputIter out,
                            Function binary_op,
                            T init)
{
  ::thrust::exclusive_scan(::thrust::device,
                           ::thrust::device_pointer_cast(begin),
                           ::thrust::device_pointer_cast(end),
                           ::thrust::device_pointer_cast(out),
                           init,
                           binary_op);
}


template <typename InputIter, typename OutputIter>
void exclusive_scan_inplace(const cuda_exec_base& exec,
                            InputIter begin,
                            InputIter end,
                            OutputIter out)
{
  using Value = typename std::iterator_traits<InputIter>::value_type;
  exclusive_scan(exec, begin, out, ::thrust::plus<Value>{}, Value{0});
}

}  // closing brace for RAJA namespace

#endif  // closing endif for RAJA_ENABLE_CUDA guard

#endif  // closing endif for header file include guard
