//
// Copyright (c) 2012 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// Renderer11.h: Defines a back-end specific class for the D3D11 renderer.

#ifndef LIBGLESV2_RENDERER_RENDERER11_H_
#define LIBGLESV2_RENDERER_RENDERER11_H_

#define GL_APICALL
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#define EGLAPI
#include <EGL/egl.h>

#include <dxgi.h>
#include <d3d11.h>

#include "common/angleutils.h"

#include "libGLESv2/renderer/Renderer.h"

namespace rx
{

class Renderer11 : public Renderer
{
  public:
    Renderer11(egl::Display *display, HDC hDc);
    virtual ~Renderer11();

    virtual EGLint initialize();
    virtual bool resetDevice();

    virtual int generateConfigs(ConfigDesc **configDescList);
    virtual void deleteConfigs(ConfigDesc *configDescList);

    virtual void startScene();
    virtual void endScene();

    virtual void sync(bool block);

    virtual void setSamplerState(gl::SamplerType type, int index, const gl::SamplerState &sampler);
    virtual void setTexture(gl::SamplerType type, int index, gl::Texture *texture);

    // lost device
    virtual void markDeviceLost();
    virtual bool isDeviceLost();
    virtual bool testDeviceLost(bool notify);
    virtual bool testDeviceResettable();

    // Renderer capabilities
    virtual DWORD getAdapterVendor() const;
    virtual const char *getAdapterDescription() const;
    virtual GUID getAdapterIdentifier() const;

    virtual bool getDXT1TextureSupport();
    virtual bool getDXT3TextureSupport();
    virtual bool getDXT5TextureSupport();
    virtual bool getEventQuerySupport();
    virtual bool getFloat32TextureSupport(bool *filtering, bool *renderable);
    virtual bool getFloat16TextureSupport(bool *filtering, bool *renderable);
    virtual bool getLuminanceTextureSupport();
    virtual bool getLuminanceAlphaTextureSupport();
    virtual bool getVertexTextureSupport() const;
    virtual bool getNonPower2TextureSupport() const;
    virtual bool getDepthTextureSupport() const;
    virtual bool getOcclusionQuerySupport() const;
    virtual bool getInstancingSupport() const;
    virtual bool getTextureFilterAnisotropySupport() const;
    virtual float getTextureMaxAnisotropy() const;
    virtual bool getShareHandleSupport() const;

    virtual bool getShaderModel3Support() const;
    virtual float getMaxPointSize() const;
    virtual int getMaxTextureWidth() const;
    virtual int getMaxTextureHeight() const;
    virtual bool get32BitIndexSupport() const;
    virtual int getMinSwapInterval() const;
    virtual int getMaxSwapInterval() const;

    virtual GLsizei getMaxSupportedSamples() const;

    // D3D11-renderer specific methods
    ID3D11Device *getDevice() { return mD3d11; }
    ID3D11DeviceContext *getDeviceContext() { return mDeviceContext; };

  private:
    DISALLOW_COPY_AND_ASSIGN(Renderer11);

    HMODULE mD3d11Module;
    HMODULE mDxgiModule;
    HDC mDc;

    bool mDeviceLost;

    void initializeDevice();
    void releaseDeviceResources();

    ID3D11Device *mD3d11;
    ID3D11DeviceContext *mDeviceContext;
};

}
#endif // LIBGLESV2_RENDERER_RENDERER11_H_