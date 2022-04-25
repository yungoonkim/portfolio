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
	//CRavidPolygon* pRect1 = (CRavidPolygon*)pTeachingObject->GetAt(0);
	CRavidRect<double>* pRect1 = (CRavidRect<double>*)pTeachingObject->GetAt(0);
	//abc = pRect1;
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
	
		DoExercise(imgInfoInspect);
		
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

void CEventHandlerExample::DrawGraph1(CRavidGraphView* pGraph, const std::vector<CRavidPoint<double>>& vctData, double dblStd, double dblStd1)
{
	do
	{
		if (!pGraph)
			break;

		pGraph->ClearPlotInfo();

		if (vctData.empty())
			break;

		CRavidGraphViewPlotInfomation rgvDataStd;
		rgvDataStd.SetPlotType(ERavidGraphViewPlotType_Line);
		rgvDataStd.SetLineColor(LIGHTRED);
		rgvDataStd.SetLineWidth(1);

		bool bCheckNGPrev = vctData[0].y > dblStd || vctData[0].y == 0;

		CRavidGraphViewPlotInfomation rgvData;
		rgvData.SetPlotType(ERavidGraphViewPlotType_DotWithLine);
		rgvData.SetLineWidth(1);

		if (!bCheckNGPrev)
		{
			rgvData.SetLineColor(LIME);
			rgvData.SetDotColor(LIME);
		}
		else
		{
			rgvData.SetLineColor(LIGHTRED);
			rgvData.SetDotColor(LIGHTRED);
		}

		bool bCheckNGPrev1 = vctData[0].y < dblStd1 || vctData[0].y == 0;

		CRavidGraphViewPlotInfomation rgvData1;
		rgvData.SetPlotType(ERavidGraphViewPlotType_DotWithLine);
		rgvData.SetLineWidth(1);

		if (!bCheckNGPrev1)
		{
			rgvData1.SetLineColor(LIME);
			rgvData1.SetDotColor(LIME);
		}
		else
		{
			rgvData1.SetLineColor(LIGHTRED);
			rgvData1.SetDotColor(LIGHTRED);
		}

		try
		{
			for (auto& rp : vctData)
			{
				bool bCheckNG = (rp.y < dblStd || rp.y == 0 || rp.y > dblStd1); // check NG status
				if (bCheckNGPrev != bCheckNG)
				{
					pGraph->AddPlotInfo(&rgvData); // add previous plot info

					rgvData.ClearPlot(); // new plot info
					rgvData.SetPlotType(ERavidGraphViewPlotType_DotWithLine);

					rgvData.SetLineWidth(1);

					if (bCheckNG) // current is NG
					{
						rgvData.SetLineColor(LIGHTRED);
						rgvData.SetDotColor(LIGHTRED);
					}
					else
					{
						rgvData.SetLineColor(LIME);
						rgvData.SetDotColor(LIME);
					}

					bCheckNGPrev = bCheckNG;
				}

				rgvData.AddPlot(rp.x, rp.y);
				rgvDataStd.AddPlot(rp.x, dblStd);
			}

			pGraph->AddPlotInfo(&rgvData);
			pGraph->AddPlotInfo(&rgvDataStd);

			pGraph->DrawGraph();
		}
		catch (const std::exception&)
		{
			pGraph->ClearPlotInfo();
		}
	} while (false);
}


bool CEventHandlerExample::DoExercise(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CModelInfo* pModel = CModelManager::GetModelInfo(0);

	if (!pModel)
		return -1;

	SType0ModelParam sData;

	if (!pModel->GetData(&sData, sizeof(SType0ModelParam)))
		return -1;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView0_Floppy;
	riImageView0_Floppy.Copy(imgInfoInspct);


	CLineGauge lg;
	lg.SetTransitionType(CLineGauge::ETransitionType_BWorWB);
	lg.SetTransitionChoice(CLineGauge::ETransitionChoice_LargestAmplitude);
	lg.SetThreshold(20);
	lg.SetMinimumAmplitude(10);
	lg.SetThickness(1);
	lg.SetSamplingStep(5.000);
	lg.SetOutLiersThreshold(1.000);
	lg.SetNumOfPass(10);
	lg.SetMeasurementRegion(m_rrMeasurement);

	lg.Measure(&riImageView0_Floppy);

	CRavidLine<double> rlMeasuredObject;
	std::vector<CRavidPoint<double> > vctMeasuredValidPoints;
	std::vector<CRavidPoint<double> > vctMeasuredInvalidPoints;

	lg.GetMeasuredObject(rlMeasuredObject);
	lg.GetMeasuredValidPoints(vctMeasuredValidPoints);
	lg.GetMeasuredInvalidPoints(vctMeasuredInvalidPoints);

	imgInfo.Swap(riImageView0_Floppy);



	//rlMeasuredObject.rpPoints[0].y -= 160;
	//rlMeasuredObject.rpPoints[1].y -= 160;
	rlMeasuredObject.rpPoints[0].y -= sData.Yoffset;
	rlMeasuredObject.rpPoints[1].y -= sData.Yoffset;
	CPointGauge pg;
	pg.SetTransitionType(CPointGauge::ETransitionType_WB);
	pg.SetTransitionChoice(CPointGauge::ETransitionChoice_All);
	pg.SetThreshold(20);
	pg.SetMinimumAmplitude(10);
	pg.SetThickness(1);
	pg.SetMeasurementRegion(rlMeasuredObject);

	std::vector<CMultipleVariable> vctResults;



	do
	{
		CRavidImageView* pView = dynamic_cast<CRavidImageView*>(CUIManager::FindView(typeid(CRavidImageView), 0));
		CRavidImageViewLayer* pLayer0 = pView->GetLayer(0);
		if (!pLayer0)
			break;

		pLayer0->Clear();
		pLayer0->Show(true);


		pg.Measure(&riImageView0_Floppy);

		std::vector<CRavidPoint<double>> vctMeasuredPoints;

		pg.GetMeasuredPoints(vctMeasuredPoints);


		pLayer0->DrawShape(CRavidLine<double>(rlMeasuredObject.rpPoints[0], rlMeasuredObject.rpPoints[1]), LIGHTRED, 2);
		double dot = 0;
		int state = 0;


		CRavidGraphView* pRgvHisto = dynamic_cast<CRavidGraphView*>(CUIManager::FindView(typeid(CRavidGraphView), 5));

		if (!pRgvHisto)
			break;

		// draw histogram graph
		pRgvHisto->ClearPlotInfo();
		pRgvHisto->SetXAxisUnit(_T("X (Value)"));
		pRgvHisto->SetYAxisUnit(_T("Y (Index)"));

		std::vector<CRavidPoint<double>> vctData;

		int nCnt = 0;
		double dPlot = 0;


		for (auto& r : vctMeasuredPoints)
		{
			pLayer0->DrawShape(r, LIGHTGREEN, 5);

			if (r.x > 10)
			{
				if (r.x - dot > sData.maxDiff)
					//if (r.x - xInfo > 60 || r.x - xInfo < 50)
				{
					pLayer0->DrawShape(r, LIGHTRED, 5);
					state = 1;
				}
				dPlot = r.x - dot;
			}

			dot = r.x;

			vctData.push_back(CRavidPoint<double>((double)nCnt, dPlot));
			nCnt++;
		}
		DrawGraph1(pRgvHisto, vctData, sData.minDiff, sData.maxDiff);
		//DrawGraph1(pRgvHisto, vctData, 50,60);
		imgInfo.Swap(riImageView0_Floppy);
		//imgInfo.Save(L"test.jpg");


		if (state == 0)
		{
			CString strValue;
			strValue.Format(_T("OK"));
			pLayer0->DrawTextW(CRavidPoint<int>(0, 0), strValue, GREEN, BLACK, 20);
		}
		else
		{
			CString strValue;
			strValue.Format(_T("NG"));
			pLayer0->DrawTextW(CRavidPoint<int>(0, 0), strValue, RED, BLACK, 20);

		}

		//rlMeasuredObject.rpPoints[0].y += 160;
		//rlMeasuredObject.rpPoints[1].y += 160;
		rlMeasuredObject.rpPoints[0].y += sData.Yoffset;
		rlMeasuredObject.rpPoints[1].y += sData.Yoffset;
		bReturn = true;
	} while (false);

	return bReturn;
}
