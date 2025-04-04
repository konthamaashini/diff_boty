#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/gazebo.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Vector3.hh>

namespace gazebo
{
  class ConstantForcePlugin : public ModelPlugin
  {
  public:
    void Load(physics::ModelPtr _model, sdf::ElementPtr) override
    {
      this->model = _model;
      this->link = model->GetLink("body_link");  // <-- UPDATE this if needed

      if (!this->link)
      {
        gzerr << "[ERROR] Link 'body_link' not found in model! Plugin will not apply force.\n";
        return;
      }

      gzmsg << "[INFO] ConstantForcePlugin loaded! Applying force on " << this->link->GetName() << "\n";

      this->updateConnection = event::Events::ConnectWorldUpdateBegin(
        std::bind(&ConstantForcePlugin::OnUpdate, this));
    }

    void OnUpdate()
    {
      if (!this->link)
      {
        gzerr << "[ERROR] Link is null. Force cannot be applied!\n";
        return;
      }

      ignition::math::Vector3d force(500, 0, 0);  // Big force for test
      this->link->AddRelativeForce(force);

      gzdbg << "[DEBUG] Applied force: " << force << " on " << this->link->GetName() << "\n";
    }

  private:
    physics::ModelPtr model;
    physics::LinkPtr link;
    event::ConnectionPtr updateConnection;
  };

  // FULLY QUALIFIED FOR SAFETY:
  GZ_REGISTER_MODEL_PLUGIN(gazebo::ConstantForcePlugin)
}
