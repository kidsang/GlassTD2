#pragma once
#ifndef __FILE_UTILSOGREDSHOW_PRIVATE_INCLUDED
#define __FILE_UTILSOGREDSHOW_PRIVATE_INCLUDED
 
//#include <Qedit.h>// for sample grabber
#include <dshow.h>
#include <WTypes.h>
// <hack>
// Vite Falcon: Nasty hack to avoid the missing 'qedit.h'
#include <windows.h>
 
EXTERN_C const CLSID CLSID_SampleGrabber;
class DECLSPEC_UUID("C1F400A0-3F08-11d3-9F0B-006008039E37")
	SampleGrabber;
 
EXTERN_C const CLSID CLSID_NullRenderer;
class DECLSPEC_UUID("C1F400A4-3F08-11d3-9F0B-006008039E37")
	NullRenderer;
 
EXTERN_C const IID IID_ISampleGrabberCB;
MIDL_INTERFACE("0579154A-2B53-4994-B0D0-E773148EFF85")
ISampleGrabberCB : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE SampleCB( 
		double SampleTime,
		IMediaSample *pSample) = 0;
 
	virtual HRESULT STDMETHODCALLTYPE BufferCB( 
		double SampleTime,
		BYTE *pBuffer,
		long BufferLen) = 0;
 
};
 
EXTERN_C const IID IID_ISampleGrabber;
MIDL_INTERFACE("6B652FFF-11FE-4fce-92AD-0266B5D7C78F")
ISampleGrabber : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE SetOneShot( 
		BOOL OneShot) = 0;
 
	virtual HRESULT STDMETHODCALLTYPE SetMediaType( 
		const AM_MEDIA_TYPE *pType) = 0;
 
	virtual HRESULT STDMETHODCALLTYPE GetConnectedMediaType( 
		AM_MEDIA_TYPE *pType) = 0;
 
	virtual HRESULT STDMETHODCALLTYPE SetBufferSamples( 
		BOOL BufferThem) = 0;
 
	virtual HRESULT STDMETHODCALLTYPE GetCurrentBuffer( 
		/* [out][in] */ long *pBufferSize,
		/* [out] */ long *pBuffer) = 0;
 
	virtual HRESULT STDMETHODCALLTYPE GetCurrentSample( 
		/* [retval][out] */ IMediaSample **ppSample) = 0;
 
	virtual HRESULT STDMETHODCALLTYPE SetCallback( 
		ISampleGrabberCB *pCallback,
		long WhichMethodToCallback) = 0;
 
};
// </hack>
 
namespace OgreUtils
{
    struct DirectShowData
    {
        /// Graph object
        IGraphBuilder *pGraph;
        /// Media control object
        IMediaControl *pControl;
        /// Media event object
        IMediaEvent *pEvent;
        /// Grabber filter
        IBaseFilter *pGrabberF;
        /// Grabber object
        ISampleGrabber *pGrabber;
        /// Interface for seeking object
        IMediaSeeking *pSeeking;
        /// Window interface
        /** Useful for some configuration
        */
        IVideoWindow *pWindow;
 
        /// Video output width
        int videoWidth;
        /// Video output height
        int videoHeight;
    };
 
    /// Util function for converting C strings to wide strings
    /** (as needed for path in directshow). */
    WCHAR* util_convertCStringToWString(const char* string);
}
 
#endif // __FILE_UTILSOGREDSHOW_PRIVATE_INCLUDED