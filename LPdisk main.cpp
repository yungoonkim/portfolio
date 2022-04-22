#include "stdafx.h"
#include "EventHandlerExample.h"
#include"mannager.h"



CEventHandlerExample::CEventHandlerExample()
{

}


CEventHandlerExample::~CEventHandlerExample()
{

}

void CEventHandlerExample::OnInspect( Algorithms::CRavidImage* pImgInfo,  int nInspectionType,  CRavidImageView* pView,  int nChannel)
{
	do
	{
		OnStartInspection(pView);
		
	} while (false);

}
void CEventHandlerExample::OnTeach(_In_ Algorithms::CRavidImage* pImgInfo, _In_ CTeachingObject* pTeachingObject, _In_opt_ CRavidImageView* pView, _In_opt_ int nChannel)
{
	pView->GetLayer(0)->Clear();

	CRavidRect<double>* pRect1 = (CRavidRect<double>*)pTeachingObject->GetAt(0);

	m_rrMeasurement = pRect1;

	pView->GetLayer(0)->DrawShape(pRect1, GREEN, 1);

	pView->Invalidate();


	

}

bool CEventHandlerExample::OnStartInspection(_In_ CRavidImageView* pView)
{
	bool bReturn = false;
	float flnspTime = 0.0f; //검사시간

	CRavidImage* pImgInfo = nullptr;

	do
	{
		if (!pView)
			break;

		CRavidImageViewLayer* pLayer0 = pView->GetLayer(0);
		CRavidImageViewLayer* pLayer1 = pView->GetLayer(1);
		CRavidImageViewLayer* pLayer2 = pView->GetLayer(2);

		if (!pLayer0 || !pLayer1 || !pLayer2)
			break;

		pLayer0->Clear();
		pLayer1->Clear();
		pLayer2->Clear();

		pImgInfo = pView->GetImageInfo();

		if (!pImgInfo)
			break;

		CPerformanceCounter pc;

		CRavidImage imgInfoInspect(pImgInfo);
		//Inspection
	
	
		DoConnet_Circle(imgInfoInspect);
		
		pImgInfo->Copy(imgInfoInspect);
		
		
		flnspTime = pc.GetElapsedTime();

		//////////////////////////////////////////////////////  View 2
		CRavidImage imgView2;
		imgView2.Copy(imgInfoInspect);

		CRavidImageView* pView2 = dynamic_cast<CRavidImageView*>(CUIManager::FindView(typeid(CRavidImageView), 1));
		CRavidImage* pImgInfo2 = nullptr;
		pView2->Open(L"C.bmp");

		pImgInfo2 = pView2->GetImageInfo();
		pImgInfo2->Copy(imgView2);
		pView2->ZoomFit();
		////////////////////////////////////////////////////  View 2
		//ConnectedComponentMask(imgInfoInspect);
		
		
		CString strValue;
		strValue.Format(_T("Time : %d ms"), (int)flnspTime);
		pLayer0->DrawText(CRavidPoint<int>(0, 20), strValue, LIME, BLACK, 20);
		pView->Invalidate(false);

		bReturn = true;

	} while (false);

	return bReturn;
}






bool CEventHandlerExample::DoConnet_Circle(_In_ CRavidImage& imgInfo)
{

	std::vector<CRavidRect<int>> vctRects;
	std::vector<CRavidRect<int>> vctRects1;
	bool bReturn = false;
	CRavidImage imgInfoInspect(imgInfo);
	CRavidImage image;
	image.Copy(imgInfoInspect);

	CMultipleVariable rmvThreshold;
	rmvThreshold.AddValue(100.000);

	CConnectedComponent cc;  //Large circle 검출

	cc.SetSingleThreshold(rmvThreshold);
	cc.SetLogicalCondition(ELogicalCondition_Less);
	cc.SetMultipleChannelCondition(CConnectedComponent::EMultipleChannelCondition_1);

	cc.Encode(&image, &m_rrMeasurement);
	vctRects = cc.GetBoundary();

	double dblFilterValue0 = 30.000;
	cc.Filter(CConnectedComponent::EFilterItem_Area, dblFilterValue0, ELogicalCondition_Less);

	CRavidCircle<double> rcMeasurement;
	for (auto& r : vctRects)
	{
		rcMeasurement.rpCenter.x = vctRects[0].GetCenter().x;
		rcMeasurement.rpCenter.y = vctRects[0].GetCenter().y;
		rcMeasurement.radius = vctRects[0].GetWidth() / 2;
	}
	rcMeasurement.startDeg = 0.0000000;
	rcMeasurement.deltaDeg = 360.0000000;
	double dblTolerance = 25.750;

	CCircleGauge cg;
	cg.SetTransitionType(CCircleGauge::ETransitionType_BWorWB);
	cg.SetTransitionChoice(CCircleGauge::ETransitionChoice_LargestAmplitude);
	cg.SetThreshold(20);
	cg.SetMinimumAmplitude(10);
	cg.SetThickness(1);
	cg.SetSamplingStep(5.000);
	cg.SetOutLiersThreshold(1.000);
	cg.SetNumOfPass(1);
	cg.SetMeasurementRegion(rcMeasurement, dblTolerance);
	//////////////////////////////////////////////////////////////////////////////////////////
	CConnectedComponent cc1; // Small circle 검출

	cc1.SetSingleThreshold(rmvThreshold);
	cc1.SetLogicalCondition(ELogicalCondition_Greater);
	cc1.SetMultipleChannelCondition(CConnectedComponent::EMultipleChannelCondition_1);

	cc1.Encode(&image, nullptr);
	vctRects = cc1.GetBoundary();

	double dblFilterValue1 = 200.000;
	cc1.Filter(CConnectedComponent::EFilterItem_BoundingBoxWidth, dblFilterValue1, ELogicalCondition_Greater);

	


	CRavidCircle<double> rcMeasurement1;
	for (auto& r : vctRects)
	{
		rcMeasurement1.rpCenter.x = vctRects[1].GetCenter().x;
		rcMeasurement1.rpCenter.y = vctRects[1].GetCenter().y;
		rcMeasurement1.radius = vctRects[1].GetWidth() / 2;
	}
	rcMeasurement1.startDeg = 0.0000000;
	rcMeasurement1.deltaDeg = 360.0000000;

	double dblTolerance1 = 21.750;

	CCircleGauge cg1;
	cg1.SetTransitionType(CCircleGauge::ETransitionType_BWorWB);
	cg1.SetTransitionChoice(CCircleGauge::ETransitionChoice_LargestAmplitude);
	cg1.SetThreshold(20);
	cg1.SetMinimumAmplitude(10);
	cg1.SetThickness(1);
	cg1.SetSamplingStep(5.000);
	cg1.SetOutLiersThreshold(1.000);
	cg1.SetNumOfPass(1);
	cg1.SetMeasurementRegion(rcMeasurement1, dblTolerance1);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CRavidGeometryArray pRga;
	rcMeasurement.GetSubtractionRegion(rcMeasurement1, &pRga); // Large circle - Small circle

	CConnectedComponent cc2;

	cc2.SetSingleThreshold(70);
	cc2.SetLogicalCondition(ELogicalCondition_Greater);
	cc2.SetMultipleChannelCondition(CConnectedComponent::EMultipleChannelCondition_1);

	cc2.Encode(&image, &pRga);


	//vctRects = cc2.GetBoundary();

	double dblFilterValue2 = 15.000;
	cc2.Filter(CConnectedComponent::EFilterItem_BoundingBoxWidth, dblFilterValue2, ELogicalCondition_Less);

	double dblFilterValue3 = 300.000;
	cc2.Filter(CConnectedComponent::EFilterItem_BoundingBoxWidth, dblFilterValue3, ELogicalCondition_Greater);
	

	vctRects1 = cc2.GetBoundary();
	
	do
	{

		CRavidImageView* pView = dynamic_cast<CRavidImageView*>(CUIManager::FindView(typeid(CRavidImageView), 0));
		CRavidImageViewLayer* pLayer0 = pView->GetLayer(0);


		if (!pLayer0)
			break;

		pLayer0->Clear();
		pLayer0->Show(true);

		cg.Measure(&image);


		CRavidCircle<double> rcMeasuredObject;
		std::vector<CRavidPoint<double> > vctMeasuredValidPoints;
		std::vector<CRavidPoint<double> > vctMeasuredInvalidPoints;

		cg.GetMeasuredObject(rcMeasuredObject);
		cg.GetMeasuredValidPoints(vctMeasuredValidPoints);
		cg.GetMeasuredInvalidPoints(vctMeasuredInvalidPoints);

		cg1.Measure(&image);
		CRavidCircle<double> rcMeasuredObject1;
		std::vector<CRavidPoint<double> > vctMeasuredValidPoints1;
		std::vector<CRavidPoint<double> > vctMeasuredInvalidPoints1;

		cg1.GetMeasuredObject(rcMeasuredObject1);
		cg1.GetMeasuredValidPoints(vctMeasuredValidPoints1);
		cg1.GetMeasuredInvalidPoints(vctMeasuredInvalidPoints1);



		imgInfo.Swap(image);

        //   Center point(Large circle, Small circle, Large circle connected conponent area, Small circle connected conponent area)
		pLayer0->DrawShape(CRavidPoint<int>(vctRects[0].GetCenter().x, vctRects[0].GetCenter().y), RED, 2);
		pLayer0->DrawShape(CRavidPoint<int>(vctRects[1].GetCenter().x, vctRects[1].GetCenter().y), RED, 2);
		pLayer0->DrawShape(CRavidPoint<int>(rcMeasuredObject.GetCenter().x, rcMeasuredObject.GetCenter().y), RED, 2);
		pLayer0->DrawShape(CRavidPoint<int>(rcMeasuredObject1.GetCenter().x, rcMeasuredObject1.GetCenter().y), RED, 2);
		
		//Large circle, Small circle, Large circle connected conponent area, Small circle connected conponent area
		pLayer0->DrawShape(vctRects[0], LIGHTGREEN, 2);
		pLayer0->DrawShape(rcMeasuredObject, LIGHTGREEN, 2);
		pLayer0->DrawShape(vctRects[1], LIGHTGREEN, 2);
		pLayer0->DrawShape(rcMeasuredObject1, LIGHTGREEN, 2);
		
		//이물질 검출 
		pLayer0->DrawShape(vctRects1[0], LIGHTRED, 2);

		//pLayer0->DrawShape(pRga, YELLOW, 1);





		bReturn = true;
	} while (false);
	return bReturn;
}


