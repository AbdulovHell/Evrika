#pragma once
namespace Evrika {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace GMap::NET;
	using namespace GMap::NET::WindowsForms;
	using namespace GMap::NET::WindowsForms::Markers;

	/// <summary>
	/// —водка дл€ mapform
	/// </summary>
	public ref class mapform : public System::Windows::Forms::Form
	{
	public:
		mapform(void)
		{
			this->SendToBack();
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			gMapControl1->Position = PointLatLng(55.736572, 37.967640);
			gMapControl1->MapProvider = MapProviders::GoogleMapProvider::Instance;
			gMapControl1->MinZoom = 1;
			gMapControl1->MaxZoom = 20;
			gMapControl1->Zoom = 12;
			gMapControl1->Manager->Mode = AccessMode::ServerAndCache;	//ServerAndCache;
			gMapControl1->CacheLocation = MapPath;
			mrkrOvrl = gcnew GMap::NET::WindowsForms::GMapOverlay();
			areaOvrl = gcnew GMap::NET::WindowsForms::GMapOverlay();
			myPosOvrl = gcnew GMap::NET::WindowsForms::GMapOverlay();
			gMapControl1->Overlays->Add(mrkrOvrl);
			gMapControl1->Overlays->Add(areaOvrl);
			gMapControl1->Overlays->Add(myPosOvrl);
			gMapControl1->DisableFocusOnMouseEnter = true;
			mymap = gMapControl1;
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~mapform()
		{
			if (components)
			{
				delete components;
			}
		}
	private: GMap::NET::WindowsForms::GMapControl^  gMapControl1;
	protected:
	public:
		GMap::NET::WindowsForms::GMapOverlay ^mrkrOvrl;
		GMap::NET::WindowsForms::GMapOverlay ^areaOvrl;
		GMap::NET::WindowsForms::GMapOverlay ^myPosOvrl;
		static GMapControl^ mymap;
		static String^ MapPath = "C:\\EvrikaGMapCache";
		GMapControl^ getMapPointer() {
			return gMapControl1;
		}
	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->gMapControl1 = (gcnew GMap::NET::WindowsForms::GMapControl());
			this->SuspendLayout();
			this->gMapControl1->Bearing = 0;
			this->gMapControl1->CanDragMap = true;
			this->gMapControl1->CausesValidation = false;
			this->gMapControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->gMapControl1->EmptyTileColor = System::Drawing::Color::Navy;
			this->gMapControl1->GrayScaleMode = false;
			this->gMapControl1->HelperLineOption = GMap::NET::WindowsForms::HelperLineOptions::DontShow;
			this->gMapControl1->LevelsKeepInMemmory = 5;
			this->gMapControl1->Location = System::Drawing::Point(0, 0);
			this->gMapControl1->MarkersEnabled = true;
			this->gMapControl1->MaxZoom = 20;
			this->gMapControl1->MinZoom = 1;
			this->gMapControl1->MouseWheelZoomType = GMap::NET::MouseWheelZoomType::MousePositionAndCenter;
			this->gMapControl1->Name = L"gMapControl1";
			this->gMapControl1->NegativeMode = false;
			this->gMapControl1->PolygonsEnabled = true;
			this->gMapControl1->RetryLoadTile = 0;
			this->gMapControl1->RoutesEnabled = true;
			this->gMapControl1->ScaleMode = GMap::NET::WindowsForms::ScaleModes::Integer;
			this->gMapControl1->SelectedAreaFillColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(33)),
				static_cast<System::Int32>(static_cast<System::Byte>(65)), static_cast<System::Int32>(static_cast<System::Byte>(105)), static_cast<System::Int32>(static_cast<System::Byte>(225)));
			this->gMapControl1->ShowTileGridLines = false;
			this->gMapControl1->Size = System::Drawing::Size(825, 435);
			this->gMapControl1->TabIndex = 0;
			this->gMapControl1->Zoom = 12;
			this->gMapControl1->OnMapDrag += gcnew GMap::NET::MapDrag(this, &mapform::gMapControl1_OnMapDrag);
			this->gMapControl1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &mapform::gMapControl1_KeyPress);
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
			this->ClientSize = System::Drawing::Size(825, 435);
			this->ControlBox = false;
			this->Controls->Add(this->gMapControl1);
			this->Name = L"mapform";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"   ";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void gMapControl1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		switch (e->KeyChar)
		{
		case '+':
			this->gMapControl1->Zoom++;
			break;
		case '-':
			this->gMapControl1->Zoom--;
			break;
		case 50:
			this->gMapControl1->Position = PointLatLng(this->gMapControl1->Position.Lat - 0.03 / (double)this->gMapControl1->Zoom, this->gMapControl1->Position.Lng);
			break;
		case 52:
			this->gMapControl1->Position = PointLatLng(this->gMapControl1->Position.Lat, this->gMapControl1->Position.Lng - 0.05 / (double)this->gMapControl1->Zoom);
			break;
		case 54:
			this->gMapControl1->Position = PointLatLng(this->gMapControl1->Position.Lat, this->gMapControl1->Position.Lng + 0.05 / (double)this->gMapControl1->Zoom);
			break;
		case 56:
			this->gMapControl1->Position = PointLatLng(this->gMapControl1->Position.Lat + 0.03 / (double)this->gMapControl1->Zoom, this->gMapControl1->Position.Lng);
			break;
		default:
			//gMapControl1->Position = PointLatLng(0, 0);
			this->Text = "key: " + (int)(e->KeyChar);
			break;
		}
	}
	private: System::Void gMapControl1_OnMapDrag();
};
}
